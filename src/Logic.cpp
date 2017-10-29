#include "Logic.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

Logic::Logic() {

    //entities_["Character"] = character_;

    //Character character_ = Character();
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

}

void Logic::load(std::string filename) {
    return;
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
