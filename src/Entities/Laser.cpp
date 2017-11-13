//
// Created by Ruoying Hao on 10/31/17.
//

#include "Entities/Laser.hpp"

#include "Logic.hpp"

Laser::Laser(){

}


void Laser::update(float delta, int &logic){}

void Laser::render (sf::RenderWindow *window) {
    sprite_.setPosition(pos_);
    window->draw(sprite_);

}

void Laser::setPos(sf::Vector2f pos){
    pos_=pos;
    sprite_.setOrigin(sprite_.getLocalBounds().width/2,sprite_.getLocalBounds().height/2);

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

sf::Vector2f Laser::getPos(){
    return pos_;
}

void Laser::setDirection(int dir){
    dir_=dir;
}

int Laser::getDirection(){
    return dir_;
}

void Laser::rotate(float angle){

    sprite_.rotate(angle);

}

bool Laser::isHacked(){
    return hacked;
}

void Laser::setTexture(sf::Texture tex){
    sprite_.setTexture(tex);
    this->setSprite(sprite_);

}

void Laser::setSprite(sf::Sprite sprite){
    sprite_ = sprite;

}