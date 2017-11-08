#include "Logic.hpp"

#include <sstream>
#include <fstream>

Logic::Logic() {
    time_left_ = 10 * 60;
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
    loadDevices(filename);
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
std::map<std::string,Device>& Logic::getDevices() {
    return devices_;
}

Entity Logic::getCharacter(){
    return entities_["Character"];
}

void Logic::registerMoveInput(Logic::Direction dir) {
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

void Logic::loadDevices(std::string filename){
    devices_["Laser"]=Laser();
    devices_["Laser"].setPos(sf::Vector2f(12,12));


}
