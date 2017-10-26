#include "Logic.hpp"

#include <sstream>
#include "external/csv/csv.h"

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

float Logic::getTimeLeft(){
    return time_left_;
}

void Logic::moveCharacter(int direction) {
    // TODO this
}

void Logic::clearLevel() {
    tiles_.clear();
    entities_.clear();
}

void Logic::loadTiles(std::string filename) {
    io::LineReader file_in(filename);
    std::string line_str;
    tiles_.clear();
    int ncols = 0;
    while (char* line = file_in.next_line()) {
        line_str = std::string(line);
        if (ncols == 0) {
            ncols = std::count(line_str.begin(), line_str.end(), ',') + 1;
            //std::cout << "ncols is " << ncols << std::endl;
        }
        std::vector<int> row;
        std::stringstream rstream(line_str);
        while (rstream.good()) {
            std::string sub;
            std::getline(rstream, sub, ',');
            row.push_back(std::stoi(sub));
        }
        tiles_.push_back(row);
    }
}

void Logic::loadEntities(std::string filename) {
    // dummy behavior, creating the character entity
    entities_["Character"] = Character();
    entities_["Character"].setVel(sf::Vector2f(1,1));
}
