//
// Created by Ruoying Hao on 10/31/17.
//
#include "Entities/Device.hpp"
#include "Logic.hpp"

Device::Device(sf::Vector2f pos, float startRotate, float endRotate, float shootTime, float stopTime ){
    pos_=pos;
    startRotate_=startRotate;
    endRotate_=endRotate;
    shootTime_=shootTime;
    stopTime_=shootTime;


};

void Device::update(float delta, int &logic){};

void Device::render (sf::RenderWindow *window) {
    sprite_.setPosition(pos_);
    window->draw(sprite_);

}

void Device::setPos(sf::Vector2f pos){
    pos_=pos;
    sprite_.setOrigin(sprite_.getLocalBounds().width/2,sprite_.getLocalBounds().height/2);

}

sf::Vector2f Device::getPos(){
    return pos_;
}

void Device::setDirection(int dir){
    dir_=dir;
}

int Device::getDirection(){
    return dir_;
}

void Device::rotate(float angle){

    sprite_.rotate(angle);

}

bool Device::isHacked(){
    return hacked;
}

void Device::setTexture(sf::Texture tex){
    sprite_.setTexture(tex);
    this->setSprite(sprite_);

}

void Device::setSprite(sf::Sprite sprite){
    sprite_ = sprite;

}




