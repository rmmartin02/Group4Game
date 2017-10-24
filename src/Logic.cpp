#include "Logic.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

Logic::Logic() {
    Character character_ = Character();
    entities_["Character"] = character_;
    
    tiles_ = { 
        { -1, -1, 1, 1, 1 },
        {  1, 1, -1, -1, 1},
        {  1, 1, 1, 1, 1 },
        { -1, -1, -1, -1, 1},
        {  2,  1,  2,  1,  1},
        { 1,  2,  1,  1,  1}
    };
}

void Logic::load(std::string filename) {
    return;
}

void Logic::update(float delta) {
    // update every entity
}

std::vector<std::vector<int>> Logic::getTiles() {
    return tiles_;
}

std::map<std::string,Entity> Logic::getEntities() {
    return entities_;
}

float Logic::getTimeLeft(){
    return time_left_;
}

