#include "Logic.hpp"

Logic::Logic() {
    
}

void Logic::update(float delta) {
    // update every entity
    for (auto iter = entities_.begin(); iter != entities_.end(); iter++){
        iter->second->update(delta);
    }
}


