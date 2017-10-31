#include "Logic.hpp"

#include <sstream>
#include <fstream>

#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

#include "Box2D/Box2D.h"

Logic::Logic() {
    
    time_left_ = 10 * 60;
    
    entities_["Character"] = Character();
    entities_["Character"].setVel(sf::Vector2f(0,0));
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
    for (auto& pair : getEntities()) {
        pair.second.move(pair.second.getVel());
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

std::map<std::string,Entity>& Logic::getEntities() {
    return entities_;
}

Entity Logic::getCharacter(){
    return entities_["Character"];
}

void Logic::registerMoveInput(Logic::Direction dir){
	switch (dir){
        case Logic::Direction::UP:
			entities_["Character"].setVel(entities_["Character"].getVel()+sf::Vector2f(0,-1));
			break;
        case Logic::Direction::DOWN:
			entities_["Character"].setVel(entities_["Character"].getVel()+sf::Vector2f(0,1));
			break;
        case Logic::Direction::LEFT:
			entities_["Character"].setVel(entities_["Character"].getVel()+sf::Vector2f(-1,0));
			break;
        case Logic::Direction::RIGHT:
			entities_["Character"].setVel(entities_["Character"].getVel()+sf::Vector2f(1,0));
			break;
        case Logic::Direction::NONE:
		default:
            entities_["Character"].setVel(sf::Vector2f(0,0));
			break;
	}
}

float Logic::getTimeLeft(){
    return time_left_;
}

void Logic::clearLevel() {
    tiles_.clear();
    entities_.clear();
}

void Logic::loadTiles(std::string filename) { 
    tiles_.clear();
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
}

void Logic::loadEntities(std::string filename) {
    // dummy behavior, creating the character entity
    entities_["Character"] = Character();
    entities_["Character"].setVel(sf::Vector2f(1,1));
}
