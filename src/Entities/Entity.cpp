#include "Entities/Entity.hpp"

#include "Logic.hpp"
  
Entity::Entity(){
};

void Entity::update(float delta, int &logic){};

  //Renders entity on window using sprite

void Entity::render (sf::RenderWindow *window) {
	//std::cout << sprite_.getPosition().x << "\n";
	sprite_.setPosition(pos_);
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

void Entity::setSprite(sf::Sprite sprite){
	sprite_ = sprite;
}
void Entity::setTexture(const sf::Texture& tex){
	sprite_.setTexture(tex);
}

void Entity::attachShape(b2Shape* shape){
    coll_shape_.reset(shape);
}

b2Shape* Entity::getShape(){
    return coll_shape_.get();
}

b2Transform Entity::getTransform(){
    //b2Transform ret;
    return b2Transform(b2Vec2(pos_.x, pos_.y), b2Rot());
}

bool Entity::wallCollision() {
    return true;
}

void Entity::onTouchWall() {
    return;
}

