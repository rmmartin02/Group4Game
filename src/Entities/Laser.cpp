//
// Created by Ruoying Hao on 10/31/17.
//

#include "Entities/Laser.hpp"

#include "Logic.hpp"

Laser::Laser(){
    hacked_=false;
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
    return hacked_;
}
