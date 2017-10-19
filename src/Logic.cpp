#include "Logic.hpp"

Logic::Logic() {
    
}

void Logic::load(std::string filename) {
    return;
}

void Logic::update(float delta) {
    // update every entity
    for (auto iter = entities_.begin(); iter != entities_.end(); iter++){
        iter->second->update(delta);
    }
}

TILE_GRID& Logic::getTiles() {
    return tiles_;
}

ENTITY_MAP& Logic::getEntities() {
    return entities_;
}

float Logic::getTimeLeft(){
    return time_left_;
}

