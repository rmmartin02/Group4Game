#include "Logic.hpp"

#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

#include "Box2D/Box2D.h"

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
