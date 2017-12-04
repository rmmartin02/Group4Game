//
// Created by Ruoying Hao on 10/12/17.
//

#include "Entities/Character.hpp"

#include "VecUtil.hpp"

const float Character::MAX_SPEED = 10.0f;
const float Character::ACCELERATION = 0.4f;
const float Character::COLLISION_SIZE = 16.0f;

Character::Character(){
    b2CircleShape* collider = new b2CircleShape();
    collider->m_p.Set(0.0f, 0.0f);
    collider->m_radius = COLLISION_SIZE;
    this->attachShape(collider);
}

std::string Character::getTypeId() {
    return Entity::CHARACTER_ID;
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
        deliberateMotion(sf::Vector2f(0, getVel().y));
    }
    if (getVel().y * dir.y <= 0) {
        deliberateMotion(sf::Vector2f(getVel().x, 0));
    }
    sf::Vector2f dnorm = vecutil::normalize(dir);
    deliberateMotion( getVel() + dnorm * ACCELERATION );
    
    float sqlen = vecutil::dotProd(getVel(), getVel());
    if (sqlen > (MAX_SPEED * MAX_SPEED)) {
        deliberateMotion(vecutil::normalize(getVel()) * MAX_SPEED);
    }
}

void Character::onWallCollision(sf::Vector2f point, sf::Vector2f normal) {
    float vrestrict = vecutil::clamp(vecutil::dotProd(getVel(),
                                     vecutil::normalize(normal)),
                                     -vecutil::infinity(), 0);
    // remove from the velocity its component along the collision normal
    sf::Vector2f vadjusted = getVel() - normal * vrestrict;
    setVel(vadjusted);
    
    // reposition to no longer be inside the wall
    // this may need tweaking; not sure what is the right value to downscale by
    float downscale = 60.0f;
    sf::Vector2f padjusted = (getPos() - point) / (downscale) + getPos();
    setPos(padjusted);
}


