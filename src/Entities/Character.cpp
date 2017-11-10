//
// Created by Ruoying Hao on 10/12/17.
//

#include "Entities/Character.hpp"

const float Character::MAX_SPEED = 10.0f;

Character::Character(){
	sf::Texture texture;
	//load texture and sprite
	if (!texture.create(100, 100))
	{
    // error...
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(0, 255, 0));
	this->setSprite(sprite);
    
    b2PolygonShape* collide_box = new b2PolygonShape();
    collide_box->SetAsBox(1,1);
    this->attachShape(collide_box);
}

// Set the current velocity
void Character::setVel(sf::Vector2f vel){
    // TODO: as it is now, moving diagonally can be faster than along the axes.
    // let's decide if we want that / refactor this soon
    // TODO: this isn't polymorphing. We need to change our entity data structure.
    std::cout << "set char vel " << std::endl;
	if (vel.y > MAX_SPEED)
		vel.y = MAX_SPEED;
	if (vel.x > MAX_SPEED)
		vel.x = MAX_SPEED;
    if (vel.y < -MAX_SPEED)
        vel.y = -MAX_SPEED;
    if (vel.x < -MAX_SPEED)
        vel.x = -MAX_SPEED;
	vel_ = vel;
}
