#include "Logic.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

Logic::Logic() {

    //entities_["Character"] = character_;

    //Character character_ = Character();
    entities_["Character"] = Character();
    
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
    //std::cout << "Called update\n";
    //entities_["Character"].move(sf::Vector2f(1,1));
    entities_["Character"].move(sf::Vector2f(1,1));
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

