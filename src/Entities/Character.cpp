//
// Created by Ruoying Hao on 10/12/17.
//

#include "Entities/Character.hpp"

#include "VecUtil.hpp"

const float Character::MAX_SPEED = 10.0f;
const float Character::ACCELERATION = 0.4f;
const float Character::COLLISION_SIZE = 16.0f;

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

void Character::onMoveInput(sf::Vector2f dir) {
    if (vecutil::length(dir) == 0) {
        setVel(sf::Vector2f(0,0));
        return;
    }
    // allow for immediately switching directions
    // if directional input is opposite from current velocity along that axis,
    // reset velocity on that axis to zero. Not sure if we should keep this.
    if (getVel().x * dir.x <= 0) {
        setVel(sf::Vector2f(0, getVel().y));
    }
    if (getVel().y * dir.y <= 0) {
        setVel(sf::Vector2f(getVel().x, 0));
    }
    sf::Vector2f dnorm = vecutil::normalize(dir);
    setVel( getVel() + dnorm * ACCELERATION );
    
    float sqlen = vecutil::dotProd(getVel(), getVel());
    if (sqlen > (MAX_SPEED * MAX_SPEED)) {
        setVel(vecutil::normalize(getVel()) * MAX_SPEED);
    }
}
