#include "Global.hpp"
#include "Entities/Entity.hpp"
#include "Logic.hpp"

  
Entity::Entity(){};

void Entity::update(float delta, int &logic){};

  //Renders entity on window using sprite
void Entity::render (sf::RenderWindow *window) const{
	window->draw(sprite_);
}

// Return the current position
sf::Vector2f Entity::getPos(){
	return pos_;
}

// Place this entity at a new position
void Entity::setPos(sf::Vector2f pos){
	pos_=pos;
}

// Displace this entity relative to its current position
void Entity::move(sf::Vector2f displacement){
	pos_ = pos_ + displacement;
}

// Get the current velocity
sf::Vector2f Entity::getVel(){
	return vel_;
}

// Set the current velocity
void Entity::setVel(sf::Vector2f vel){
	vel_ = vel;
}

void Entity::setSprite(sf::Sprite sprite){
	sprite_ = sprite;
}