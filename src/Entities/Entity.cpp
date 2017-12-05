#include "Entities/Entity.hpp"

#include "VecUtil.hpp"

const std::string Entity::DEFAULT_ID = "entity";
const std::string Entity::CHARACTER_ID = "character";
const std::string Entity::ENEMY1_ID = "enemy1";
const std::string Entity::ENEMY2_ID = "enemy2";
const std::string Entity::LASER_ID = "laser";

Entity::Entity(){};

std::string Entity::getTypeId() {
    return Entity::DEFAULT_ID;
}

void Entity::update(float delta, int &logic){};

// Return the current position
sf::Vector2f Entity::getPos(){
	return pos_;
}

sf::Vector2f Entity::getCenterPos(){
	return sf::Vector2f(pos_.x-16.0f,pos_.y-16.0f);
}

// Place this entity at a new position
void Entity::setPos(sf::Vector2f pos){
	pos_=pos;
}

// Displace this entity relative to its current position
void Entity::move(sf::Vector2f displacement){
	//std::cout << "Calling move\n";
	pos_.x += displacement.x;
	pos_.y += displacement.y;
	//std::cout << "Calling move \n" << sprite_.getPosition().x <<"\n";
}

// Get the current velocity
sf::Vector2f Entity::getVel(){
	return vel_;
}

// Set the current velocity
void Entity::setVel(sf::Vector2f vel){
	vel_ = vel;
}

// Deliberately set velocity, affecting the faced direction
void Entity::deliberateMotion(sf::Vector2f vel) {
    setVel(vel);
    if ( vecutil::nonZero(vel) != 0 ) {
        dir_ = vecutil::radToDeg(vecutil::angle(vel));
    }
}

float Entity::getDirection() {
    return dir_;
}

void Entity::attachShape(b2Shape* shape){
    coll_shape_.reset(shape);
}

b2Shape* Entity::getShape(){
    return coll_shape_.get();
}

b2Transform Entity::getTransform(){
    return b2Transform(b2Vec2(pos_.x, pos_.y), b2Rot(0.0f));
}

bool Entity::canWallCollide() {
    return true;
}

void Entity::onWallCollision(sf::Vector2f point, sf::Vector2f normal) {
    return;
}

