//
// Created by Ruoying Hao on 10/12/17.
//

#include "Entities/Character.hpp"

#include "VecUtil.hpp"

const float Character::MAX_SPEED = 10.0f;
const float Character::ACCELERATION = 1.0f;
const float Character::COLLISION_SIZE = 32.0f;

Character::Character(){
	sf::Texture texture;
	//load texture and sprite
	if (!texture.create(32, 32))
	{
    // error...
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(0, 255, 0));
	this->setSprite(sprite);
    
    b2CircleShape* collider = new b2CircleShape();
    collider->m_p.Set(0.0f, 0.0f);
    collider->m_radius = COLLISION_SIZE;
    this->attachShape(collider);
}

// Set the current velocity
void Character::setVel(sf::Vector2f vel){
    float sqlen = vecutil::dotProd(vel, vel);
    if (sqlen > (MAX_SPEED * MAX_SPEED)) {
        vel = vecutil::normalize(vel) * MAX_SPEED;
    }
	vel_ = vel;
}
