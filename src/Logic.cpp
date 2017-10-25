#include "Logic.hpp"

#include <sstream>
#include "external/csv/csv.h"

Logic::Logic() {
    
}

void Logic::load(std::string filename) {
    //entities_["Character"] = character_;

    //Character character_ = Character();
    entities_["Character"] = Character();
    entities_["Character"].setVel(sf::Vector2f(1,1));
    
    tiles_ = { 
        { -1, -1, 1, 1, 1 },
        {  1, 1, -1, -1, 1},
        {  1, 1, 1, 1, 1 },
        { -1, -1, -1, -1, 1},
        {  2,  1,  2,  1,  1},
        { 1,  2,  1,  1,  1}
    };
    
    io::LineReader file_in(filename);
    std::string line_str;
    tiles_.clear();
    int ncols = 0;
    while (char* line = file_in.next_line()) {
        line_str = std::string(line);
        if (ncols == 0) {
            ncols = std::count(line_str.begin(), line_str.end(), ',') + 1;
            std::cout << "ncols is " << ncols << std::endl;
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
    
    std::cout << "nrows is " << tiles_.size() << std::endl;
}

void Logic::update(float delta) {
    // update every entity.
    for (auto& pair : getEntities()) {
        pair.second.move(pair.second.getVel());
    }
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

