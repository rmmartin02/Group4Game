#include "Logic.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

Logic::Logic() {

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

}

void Logic::load(std::string filename) {
    return;
}

void Logic::update(float delta) {
    // update every entity.
    entities_["Character"].move(entities_["Character"].getVel());
    for (auto e : getEntities()) {
        // this currently doesn't work (because it's copying the Entity objects?)
        e.second.move(e.second.getVel());
    }
}

std::vector<std::vector<int>> Logic::getTiles() {
    return tiles_;
}

std::map<std::string,Entity> Logic::getEntities() {
    return entities_;
}

Entity Logic::getCharacter(){
	return entities_["Character"];
}

float Logic::getTimeLeft(){
    return time_left_;
}

