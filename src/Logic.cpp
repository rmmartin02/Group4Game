#include "Logic.hpp"

#include <sstream>
#include <fstream>

#include "VecUtil.hpp"

Logic::Logic() {
    
    time_left_ = 10 * 60;
    
    //entities_["Character"] = Character();
    //entities_["Character"].setVel(sf::Vector2f(0,0));
    tiles_ = { 
        { -1, -1, 1, 1, 1 },
        {  1, 1, -1, -1, 1},
        {  1, 1, 1, 1, 1 },
        { -1, -1, -1, -1, 1},
        {  2,  1,  2,  1,  1},
        { 1,  2,  1,  1,  1}
    };
    
    b2Vec2 gravity(0.0f, 0.0f); // no gravity
    b2World world(gravity);
    
    // This compiles and runs without issue, so we know the Box2D lib works.
    // However...
    // we might want to use the underlying objects in the Collision module
    // instead of letting Box2D do all the physics simulation that it does
    // when you use the full World object.
    // For example, we might attach b2__Shapes to our entities instead of
    // rigid bodies. We don't need the box2D physics making everything bounce
    // around. Just the shape classes give us the ability to check for intersections
    // and even do ray casting (which will probably help with line-of-sight). 
}

void Logic::update(float delta) {
    // update every entity.
    for ( auto& pair : getEntities() ) {
        Entity& e = *(pair.second.get());
        if (e.wallCollision()){
            b2Vec2 wall_touch;
            b2Vec2 wall_norm;
            if (checkWallCollision(e, wall_touch, wall_norm)){
                //std::cout << "entity " << pair.first << " hitting wall" << std::endl;
                // restrict velocity so we don't move into walls
                // project velocity onto wall normal
                float vrestrict = vecutil::clamp(vecutil::dotProd(e.getVel(),
                                    vecutil::normalize(vecutil::toSFVec(wall_norm))),
                                                 -vecutil::infinity(), 0);
                // remove that component from the velocity
                sf::Vector2f vadjusted = e.getVel() - vecutil::toSFVec(vrestrict * wall_norm);
                e.setVel(vadjusted);
            }
            else {
                std::cout << "no wall collision" << std::endl;
            }
        }
        e.move(e.getVel());
    }
    
    // adjust the timer
    time_left_ -= delta;
    if (time_left_ < 0) {
        std::cout << "Ran out of time!" << std::endl;
    }
}

void Logic::load(std::string filename) {
    clearLevel();
    loadTiles(filename);
    loadEntities(filename);
    std::cout << "Map size: " << getMapSize().first 
              << "," << getMapSize().second << std::endl;
}

std::pair<int, int> Logic::getMapSize() {
    int cols = 0;
    if (tiles_.size() > 0) { 
        cols = tiles_[0].size();
    }
    return std::make_pair(tiles_.size(), cols);
}

std::vector<std::vector<int>>& Logic::getTiles() {
    return tiles_;
}

void Logic::addEntity(std::string id, Entity* e) {
    entities_[id] = std::unique_ptr<Entity>(e);
}

Entity& Logic::getEntity(std::string id) {
    return *(entities_[id].get());
}

ENTITY_DATA& Logic::getEntities() {
    return entities_;
}

Character& Logic::getCharacter(){
    return static_cast<Character&>(getEntity("Character"));
}

void Logic::registerMoveInput(Logic::Direction dir){
    sf::Vector2f motion(0,0);
	switch (dir){
        case Logic::Direction::UP:
			motion = sf::Vector2f(0,-1);
			break;
        case Logic::Direction::DOWN:
			motion = sf::Vector2f(0,1);
			break;
        case Logic::Direction::LEFT:
			motion = sf::Vector2f(-1,0);
			break;
        case Logic::Direction::RIGHT:
			motion = sf::Vector2f(1,0);
			break;
        case Logic::Direction::NONE:
		default:
            motion = sf::Vector2f(0,0);
            getCharacter().setVel(motion);
			return;
	}
    getCharacter().setVel(getCharacter().getVel() + motion);
}

bool Logic::getDebugInfo(sf::Vector2f& p1, sf::Vector2f& p2) {
    b2Vec2 wall_touch;
    b2Vec2 wall_norm;
    if (checkWallCollision(getCharacter(), wall_touch, wall_norm)){
        p1 = vecutil::toSFVec(wall_touch);
        p2 = vecutil::toSFVec(wall_norm);
        return true;
    }
    return false;
}

float Logic::getTimeLeft(){
    return time_left_;
}

void Logic::clearLevel() {
    tiles_.clear();
    wall_shapes_.clear();
    entities_.clear();
}

void Logic::loadTiles(std::string filename) { 
    tiles_.clear();
    wall_shapes_.clear();
    std::ifstream file_in(filename);
    if ( !file_in.is_open() ) {
        std::cout << "failed to open level file " << filename << std::endl;
        return;
    }
    std::string line_str;
    int ncols = 0;
    while ( std::getline(file_in, line_str) ) {
        if (ncols == 0) {
            ncols = std::count(line_str.begin(), line_str.end(), ',') + 1;
        }
        std::vector<int> row;
        std::stringstream rstream(line_str);
        while (rstream.good()) {
            std::string sub;
            std::getline(rstream, sub, ',');
            try {
                row.push_back(std::stoi(sub));
            }
            catch ( const std::logic_error& e ){
                std::cout << "could not parse value " << sub
                          << " in tile csv " << filename << std::endl;
            }
        }
        tiles_.push_back(row);
    }
    buildWallShapes();
}

void Logic::loadEntities(std::string filename) {
    // dummy behavior, creating the character entity
    //entities_["Character"] = Character();
    //entities_["Character"].setVel(sf::Vector2f(1,1));
    addEntity("Character", new Character());
    getCharacter().setVel(sf::Vector2f(1,1));
}

void Logic::buildWallShapes() {
    wall_shapes_.clear();
    auto map_size = getMapSize();
    
    // Currently, scans along each row and forms rectangle shapes of
    // height 1 that are as long as possible (vertical rectangles)
    int wall_start = -1;
    int wall_end = -1; // the position AFTER the last block of the wall
    for (int r = 0; r < map_size.first; r++) {
        for (int c = 0; c < map_size.second; c++) {
            if ( wall_start < 0 ) {
                if ( tileIsWall(tiles_[r][c]) )
                    wall_start = c;
            }
            if ( wall_start >= 0 ) {
                if ( !tileIsWall(tiles_[r][c]) )
                    wall_end = c;
                if ( c == map_size.second - 1 )
                    wall_end = c+1;
            }
            if ( wall_end >= 0 ) {
                std::cout << r << ": created wall from " << wall_start << " to " << wall_end << std::endl;
                b2PolygonShape* pshape = new b2PolygonShape();
                
                // center is the vector from 0,0 to the the middle of the shape
                b2Vec2 center(r + 0.5f, wall_start + (wall_end - wall_start)/(2.0f));
                center = TILE_SIZE * center;
                
                // hsize is half the size of the shape
                b2Vec2 hsize(0.5f, (wall_end - wall_start)/(2.0f));
                hsize = TILE_SIZE * hsize;
                
                std::cout << "center at " << vecutil::vecInfo(center) << std::endl;
                std::cout << "half size is " << vecutil::vecInfo(hsize) << std::endl;
                pshape->SetAsBox(hsize.x, hsize.y, // half width, half height
                                 center,
                                 0.0f); // rotation degrees
                wall_shapes_.push_back(std::unique_ptr<b2PolygonShape>(pshape));
                wall_start = -1;
                wall_end = -1;
            }
        }
    }
    
    std::cout << "HORIZONTAL----" << std::endl;
    
    // Then, generates horizontal horizontal rectangles in similar fashion
    wall_start = -1;
    wall_end = -1;
    for (int c = 0; c < map_size.second; c++) {
        for (int r = 0; r < map_size.first; r++) {
            if ( wall_start < 0 ) {
                if ( tileIsWall(tiles_[r][c]) )
                    wall_start = r;
            }
            if ( wall_start >= 0 ) {
                if ( !tileIsWall(tiles_[r][c]) )
                    wall_end = r;
                if ( r == map_size.first - 1 )
                    wall_end = r+1;
            }
            if ( wall_end >= 0 ) {
                std::cout << c << ": created wall from " << wall_start << " to " << wall_end << std::endl;
                b2PolygonShape* pshape = new b2PolygonShape();
                
                // center is the vector from 0,0 to the the middle of the shape
                b2Vec2 center(wall_start + (wall_end - wall_start)/(2.0f), c + 0.5f);
                center = TILE_SIZE * center;
                
                // hsize is half the size of the shape
                b2Vec2 hsize((wall_end - wall_start)/(2.0f), 0.5f);
                hsize = TILE_SIZE * hsize;
                
                std::cout << "center at " << vecutil::vecInfo(center) << std::endl;
                std::cout << "half size is " << vecutil::vecInfo(hsize) << std::endl;
                pshape->SetAsBox(hsize.x, hsize.y, // half width, half height
                                 center,
                                 0.0f); // rotation degrees
                wall_shapes_.push_back(std::unique_ptr<b2PolygonShape>(pshape));
                wall_start = -1;
                wall_end = -1;
            }
        }
    }
    
    std::cout << "Created " << wall_shapes_.size() << " Box2D shapes for the tiles." << std::endl;
    for (int i = 0; i < wall_shapes_.size(); i++) {
        std::cout << static_cast<int>(wall_shapes_[i]->m_type) << std::endl;
    }
}

bool Logic::tileIsWall(int tile) {
    return tile == 455 || tile == 211 || tile == -1;
}

bool Logic::checkWallCollision(Entity& e, b2Vec2& collision_pt, b2Vec2& norm) {
    if ( wall_shapes_.size() == 0 ) {
        std::cout << "Logic.cpp: tried to check collision without complete wall info" << std::endl;
        return false;   
    }
    if ( !e.getShape() ) {
        return false;
    }

    auto pt = e.getPos();
        //std::cout << "---------Wall shape: " << wall_shapes_[i]->GetType() << std::endl;
        //std::cout << vecutil::vecInfo(wall_transforms_[i].p) << std::endl;
    
    /*
    sf::Vector2f tpos = (1.0f/TILE_SIZE) * pt;
    tpos.x = (int)tpos.x;
    tpos.y = (int)tpos.y;
    if (tpos.x >= 0 && tpos.y >= 0 && tpos.x < getMapSize().first && tpos.y < getMapSize().second) {
        std::cout << "tile is " << vecutil::vecInfo(tpos) << ":" << tiles_[(int)(pt.x / TILE_SIZE)][(int)(pt.y / TILE_SIZE)] << std::endl;
    }
    else {
        std::cout << "tile " << vecutil::vecInfo(tpos) << " out of bounds" << std::endl;
    }
    //std::cout << "Reached collision checks for " << vecutil::vecInfo(pt) << std::endl;
    */
    
    float closest = vecutil::infinity();
    int num_collisions = 0;
    collision_pt = b2Vec2(0,0);
    norm = b2Vec2(0,0);
    for (int i = 0; i < wall_shapes_.size(); i++) {
        bool part_collision = b2TestOverlap( e.getShape(), 0, wall_shapes_[i].get(), 0, 
                e.getTransform(), vecutil::iform());
        if (part_collision) {
            b2Manifold manifold;
            b2CollidePolygonAndCircle(&manifold, 
                                      static_cast<b2PolygonShape*>(wall_shapes_[i].get()), vecutil::iform(),
                                      static_cast<b2CircleShape*>(e.getShape()), e.getTransform()
                                     );
            
            b2WorldManifold worldManifold;
            worldManifold.Initialize(&manifold, 
                                     vecutil::iform(), wall_shapes_[i]->m_radius,
                                     e.getTransform(), e.getShape()->m_radius
                                    );
            // circle-poly collisions generate only one manifold pt and normal
            // if we collided at all
            collision_pt += worldManifold.points[0];
            norm += worldManifold.normal;
            num_collisions ++;
            if (worldManifold.separations[0] < closest) {
                closest = worldManifold.separations[i];
            }
        }
    }
    
    std::cout << "Collided with " << num_collisions << " wall shapes" << std::endl;
    
    if (closest < vecutil::infinity()) {
        //std::cout << "normal: " << vecutil::vecInfo(norm) << std::endl;
        //std::cout << "cpoint: " << vecutil::vecInfo(collision_pt) << std::endl;
        collision_pt = (1.0f / num_collisions) * collision_pt;
        norm.Normalize();
        return true;
    }
    return false;
}

