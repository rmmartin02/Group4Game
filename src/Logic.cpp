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
    
}

void Logic::update(float delta) {
    // update every entity.
    for ( auto& pair : getEntities() ) {
        Entity& e = *(pair.second.get());
        if (e.canWallCollide()){
            handleWallCollisions(e);
        }
        e.move(e.getVel());

        //check if character is in enemies line of sight
        if (Enemy* enemy = dynamic_cast<Enemy*>(&e)){
            sf::Vector2f hit;
            sf::Vector2f last_seen_character_pos_;
            if(enemy->canSeePlayer(getCharacter().getPos()) && !sightObstructed(enemy->getPos(), getCharacter().getPos(), hit)){
                std::cout<<"Logic: Charcter in line of sight\n";
                //chase player, send out signal
                enemy->alert();
                enemy->signal(getEntities());
                last_seen_character_pos_ = getCharacter().getPos();
                //if close enough attack
                if(dist<enemy->getAttackRadius()){
                    enemy->attack();
                }
            }
            else{
                //cant see player but is alerted, so countdown
                if(enemy->isAlerted()){
                    enemy->timer(delta);
                }
            }
            if(enemy->isAlerted()){
                float dist = sqrt(pow(enemy->getPos().x-getCharacter().getPos().x,2)+pow(enemy->getPos().y-getCharacter().getPos().y,2));
                else{
                    //chase character (to last seen position)
                    enemy->setDestPos(last_seen_character_pos_);
                }
            }
            else{
                //return to patrol route/go to next patrol point

            }
        }
    }
    
    // adjust the timer
    time_left_ -= delta;
    if (time_left_ < 0) {
        std::cout << "Logic.cpp: Ran out of time!" << std::endl;
    }
}

void Logic::load(std::string mapfilename,std::string enemyfilename) {
    clearLevel();
    loadTiles(mapfilename);
    loadEntities(enemyfilename);
    std::cout << "Logic.cpp: Map size: " << getMapSize().first 
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

void Logic::registerMoveInput(sf::Vector2f dir) {
    getCharacter().onMoveInput(dir);
}

bool Logic::getDebugInfo(sf::Vector2f& p1, sf::Vector2f& p2) {
    b2Vec2 wall_touch;
    b2Vec2 wall_norm;
    //if (checkWallCollision(getCharacter(), wall_touch, wall_norm)){
      //  p1 = vecutil::toSFVec(wall_touch);
      //  p2 = vecutil::toSFVec(wall_norm);
      //  return true;
    //}
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
        std::cout << "Logic.cpp: failed to open level file " << filename << std::endl;
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
                std::cout << "Logic.cpp: could not parse value " << sub
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
    std::ifstream file(filename);
    std::string str;
    int counter=1;

    while (std::getline(file, str))
    {
        // for each line in the file:
        // n=1: basic enemy; n=2: advanced enemy; n=0 laser
        // n start_pos.x start_pos.y dest_pos.x dest_pos.y, for n=1,2
        // n pos.x pos.y start_direction end_direction, for n=0
        // n is the class of enemy/laser, determine which class of enemy to be created

        //start_pos and dest_pos are starting and destination, must not be on the wall
        std::istringstream iss(str);
        int level;
        float start_x, start_y,dest_x,dest_y;
        iss >> level >> start_x>> start_y >> dest_x >> dest_y;



        if(level==1){
            addEntity("Enemy"+std::to_string(counter),new Enemy());

            Enemy& e=static_cast<Enemy&>(getEntity("Enemy"+std::to_string(counter)));
            e.setStartPos(sf::Vector2f(start_x,start_y));
            e.setPos(sf::Vector2f(start_x,start_y));
            e.setDestPos(sf::Vector2f(dest_x,dest_y));
            //set additional enemy 1 var here

        }
        else if(level==2){
            addEntity("Enemy"+std::to_string(counter),new Enemy());

            Enemy& e=static_cast<Enemy&>(getEntity("Enemy"+std::to_string(counter)));
            e.setStartPos(sf::Vector2f(start_x,start_y));
            e.setPos(sf::Vector2f(start_x,start_y));
            e.setDestPos(sf::Vector2f(dest_x,dest_y));
            //set additional enemy 2 var here

        }
        else if(level==0){
            addEntity("Laser"+std::to_string(counter),new Laser());
            Laser& l=static_cast<Laser&>(getEntity("Laser"+std::to_string(counter)));
            l.setPos(sf::Vector2f(start_x,start_y));
            l.setDirection(dest_x);
            l.setRotate(dest_x,dest_y);


        }



        counter=counter+1;

    }

    //testing
    std::cout << "Logic.cpp: checking enemy info (enemy 3's position) " << vecutil::vecInfo(getEntity("Enemy3").getPos()) << std::endl;

}

void Logic::buildWallShapes() {
    wall_shapes_.clear();
    buildAxisWalls(true);
    buildAxisWalls(false);
    std::cout << "Logic.cpp: Created " << wall_shapes_.size() << " Box2D shapes for the tiles." << std::endl;
}

int Logic::buildAxisWalls(bool vertical) {
    int wall_start = -1;
    int wall_end = -1; // the position AFTER the last block of the wall
    
    auto map_size = getMapSize();
    
    int inner_limit = vertical ? map_size.first : map_size.second;
    int outer_limit = vertical ? map_size.second : map_size.first;
    
    for (int outer = 0; outer < outer_limit; outer++) {
        for (int inner = 0; inner < inner_limit; inner++) {
            int tile = vertical ? tiles_[inner][outer] : tiles_[outer][inner];
            if ( wall_start < 0 ) {
                if ( tileIsWall(tile) )
                    wall_start = inner;
            }
            if ( wall_start >= 0 ) {
                if ( !tileIsWall(tile) )
                    wall_end = inner;
                if ( inner == map_size.second - 1 )
                    wall_end = inner+1;
            }
            if ( wall_end >= 0 ) {
                //std::cout << outer << ": created wall from " << wall_start << " to " << wall_end << std::endl;
                b2PolygonShape* pshape = new b2PolygonShape();
                
                // center is the vector from 0,0 to the the middle of the shape
                // hsize is half the size of the shape
                b2Vec2 center;
                b2Vec2 hsize;
                if ( vertical ) {
                    center = b2Vec2(outer + 0.5f, wall_start + (wall_end - wall_start)/(2.0f));
                    hsize  = b2Vec2(0.5f, (wall_end - wall_start)/(2.0f));
                }
                else {
                    center = b2Vec2(wall_start + (wall_end - wall_start)/(2.0f), outer + 0.5f);
                    hsize  = b2Vec2((wall_end - wall_start)/(2.0f), 0.5f);
                }
                center = TILE_SIZE * center;
                hsize = TILE_SIZE * hsize;
                
                //std::cout << "center at " << vecutil::vecInfo(center) << std::endl;
                //std::cout << "half size is " << vecutil::vecInfo(hsize) << std::endl;
                pshape->SetAsBox(hsize.x, hsize.y, // half width, half height
                                 center,
                                 0.0f); // rotation degrees
                wall_shapes_.push_back(std::unique_ptr<b2PolygonShape>(pshape));
                wall_start = -1;
                wall_end = -1;
            }
        }
    }
}

bool Logic::tileIsWall(int tile) {
    return tile != 4 && tile!= 5;
}

bool Logic::handleWallCollisions(Entity& e) {
    if ( wall_shapes_.size() == 0 ) {
        std::cout << "Logic.cpp: tried to check collision without complete wall info" << std::endl;
        return false;   
    }
    if ( !e.getShape() ) {
        return false;
    }

    float closest = vecutil::infinity();
    int num_collisions = 0;
    b2Vec2 collision_pt = b2Vec2(0,0);
    b2Vec2 norm = b2Vec2(0,0);
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
            collision_pt = worldManifold.points[0];
            norm = worldManifold.normal;
            norm.Normalize();
            num_collisions ++;
            if (worldManifold.separations[0] < closest) {
                closest = worldManifold.separations[i];
            }
            e.onWallCollision(vecutil::toSFVec(collision_pt), vecutil::toSFVec(norm));
        }
    }
    
    return closest < vecutil::infinity();
}

bool Logic::sightObstructed(sf::Vector2f src, sf::Vector2f target, 
                              sf::Vector2f& hit) {
    int hit_shape = -1;
    float min_frac = vecutil::infinity();
    b2Transform itransform = vecutil::iform();
    b2RayCastOutput ray_output;
    b2RayCastInput ray_input;
    ray_input.p1 = vecutil::toB2Vec(src);
    ray_input.p2 = vecutil::toB2Vec(target);
    ray_input.maxFraction = 1.0f;
    int child;
    for (int i = 0; i < wall_shapes_.size(); i++) {
        bool rayhit = wall_shapes_[i]->RayCast(&ray_output, ray_input, itransform, child);
        if (rayhit && ray_output.fraction < min_frac) {
            min_frac = ray_output.fraction;
            hit_shape = i;
            hit = vecutil::toSFVec(ray_input.p1 + 
                                   ray_output.fraction * (ray_input.p2 - ray_input.p1));
        }
    }
    return hit_shape >= 0;
}
