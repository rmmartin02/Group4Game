#include "Logic.hpp"

#include <sstream>
#include <fstream>

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
        pair.second->move(pair.second->getVel());
        if (pair.second->wallCollision()){            
        }
    }
    
    // testing box2d integration
   // b2Transform ctrans = getCharacter().getTransform();
   // std::cout << "Transform: " << ctrans.p.x << ", " << ctrans.p.y << "." << std::endl;
    if (checkWallCollision(getCharacter())){
        std::cout << "Character hitting wall" << std::endl;
    }
    else{
        std::cout << "no wall collision" << std::endl;
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
    //sf::Sprite charSprite;
    //getCharacter().setSprite(charSprite);
    getCharacter().setVel(sf::Vector2f(1,1));

    addEntity("Character2", new Character());
    getEntity("Character2").setVel(sf::Vector2f(1,1));
    std::cout<<"loadEntities\n";
}

void Logic::buildWallShapes() {
    wall_shapes_.clear();
    auto map_size = getMapSize();
    
    // Currently, scans along each row and forms rectangle shapes of
    // height 1 that are as long horizontally as possible
    int wall_start = -1;
    int wall_end = -1; // the position AFTER the last block of the wall
    for (int r = 0; r < map_size.first; r++) {
        for (int c = 0; c < map_size.second; c++) {
            if ( wall_start < 0 ) {
                if ( tileIsWall(tiles_[r][c]) )
                    wall_start = c;
            }
            else {
                if ( !tileIsWall(tiles_[r][c]) )
                    wall_end = c;
                if ( c == map_size.second - 1 )
                    wall_end = c+1;
            }
            if ( wall_end > 0 ) {
                std::cout << "created wall from " << wall_start << " to " << (wall_end - 1) << std::endl;
                b2PolygonShape* box = new b2PolygonShape();
                box->SetAsBox((wall_end - wall_start)/(0.2f), 0.5f, b2Vec2(0,0), 0.0f);
                // add a box2d shape of length size wall_end - wall_start
                wall_shapes_.push_back(std::unique_ptr<b2PolygonShape>(box));
                // TODO verify where box2d expects the origin point of its shapes to be
                wall_transforms_.push_back(b2Transform(b2Vec2(wall_start,r), b2Rot()));
                wall_start = -1;
                wall_end = -1;
            }
        }
    }
    
    std::cout << "Created " << wall_shapes_.size() << " Box2D shapes for the tiles." << std::endl;
    for (int i = 0; i < wall_shapes_.size(); i++) {
        std::cout << static_cast<int>(wall_shapes_[i]->m_type) << std::endl;
        std::cout << static_cast<float>(wall_transforms_[i].p.x) << "," << static_cast<float>(wall_transforms_[i].p.y) << std::endl;
    }
}

bool Logic::tileIsWall(int tile) {
    return tile == 455 || tile == 211 || tile == 210 || tile == -1;
}

bool Logic::checkWallCollision(Entity& e) {
    if ( wall_shapes_.size() == 0 || wall_transforms_.size() == 0 ) {
        std::cout << "Logic.cpp: tried to check collision without complete wall info" << std::endl;
        return false;
    }
    if ( e.getShape() == nullptr ) {
        return false;
    }

    std::cout << "Reached collision checks." << std::endl;

    for (int i = 0; i < wall_shapes_.size(); i++) {
        auto part_collision = b2TestOverlap( e.getShape(), 0, wall_shapes_[i].get(), 0, 
                e.getTransform(), wall_transforms_[i]);
        if (part_collision) {
            return true;
        }
    }
    return false;
}

