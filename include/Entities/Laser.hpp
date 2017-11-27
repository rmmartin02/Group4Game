//
// Created by Ruoying Hao on 10/31/17.
//

#ifndef LASER_HPP
#define LASER_HPP

#include "Entities/Entity.hpp"

class Laser : public Entity{

protected:
    sf::Vector2f pos_;
    bool hacked_;
    sf::Sprite sprite_;
    float dir_;
    float startRotate_;
    float endRotate_;
    float shootTime_;
    float stopTime_;

public:
    Laser();


    //return direction: 0,1,2,3 -> NORTH,EAST,SOUTH,WEST
    int getDirection();


    void setRotate(float startRotate, float endRotate);

    void setShootTime(float shootTime);

    void setStopTime(float stopTime);

    void setDirection(float dir);

    //rotate the device
    void rotate(float angle);

    //void alertEnemy();

    //check if the device is hacked by the player
    bool isHacked();
    static const float COLLISION_SIZE;
};

#endif //LASER_HPP
