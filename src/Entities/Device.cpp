//
// Created by Ruoying Hao on 10/31/17.
//
#include "Global.hpp"
#include "Entities/Device.hpp"
#include "Logic.hpp"

Device::Device(){

};

void Device::update(float delta, int &logic){};

void Device::render (sf::RenderWindow *window) {
    sprite_.setPosition(pos_);
    window->draw(sprite_);

}

void Device::setPos(sf::Vector2f pos){
    pos_=pos;
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
    sprite_.rotate(10);

}

bool Device::isHacked(){
    return hacked;
}

void Device::setSprite(sf::Sprite sprite){
    sprite_ = sprite;

}


