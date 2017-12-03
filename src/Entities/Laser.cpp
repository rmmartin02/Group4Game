//
// Created by Ruoying Hao on 10/31/17.
//

#include "Entities/Laser.hpp"

const float Laser::COLLISION_SIZE = 32.0f;
Laser::Laser(){
    sf::Texture texture;
    if (!texture.create(32, 32))
    {
        // error...
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(0, 255, 200));
    this->setSprite(sprite);

    b2CircleShape* collider = new b2CircleShape();
    collider->m_p.Set(0.0f, 0.0f);
    collider->m_radius = COLLISION_SIZE;
    this->attachShape(collider);
    hacked_=false;
}

void Laser::setDirection(float angle) {
    dir_ = angle;
}

void Laser::setRotate(float startRotate, float endRotate){
    startRotate_=startRotate;
    endRotate_=endRotate;
}

void Laser::setShootTime(float shootTime){
    shootTime_=shootTime;
}

void Laser::setStopTime(float stopTime){
    stopTime_=stopTime;
}

void Laser::rotate(float angle){

    sprite_.rotate(angle);

}

bool Laser::isHacked(){
    return hacked_;
}
