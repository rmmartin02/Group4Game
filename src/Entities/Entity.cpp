#include "Global.hpp"
#include "Entities/Entity.hpp"
#include "Logic.hpp"

  
Entity::Entity(){};

void Entity::update(float delta, int &logic){};

  //Renders entity on window using sprite
void Entity::render (sf::RenderWindow *window) {
	//std::cout << sprite_.getPosition().x << "\n";
	window->draw(sprite_);
}

// Return the current position
sf::Vector2f Entity::getPos(){
	return pos_;
}

// Place this entity at a new position
void Entity::setPos(sf::Vector2f pos){
	pos_=pos;
	sprite_.setPosition(pos_);
}

// Displace this entity relative to its current position
void Entity::move(sf::Vector2f displacement){
	//std::cout << "Calling move\n";
	pos_.x += displacement.x;
	pos_.y += displacement.y;
	sprite_.setPosition(pos_);
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

void Entity::setSprite(sf::Sprite sprite){
	sprite_ = sprite;
}
