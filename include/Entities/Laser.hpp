//
// Created by Ruoying Hao on 10/31/17.
//

#ifndef LASER_HPP
#define LASER_HPP

#include "Entities/Entity.hpp"

class Laser : public Entity{

protected:
    bool hacked_;
    sf::Sprite sprite_;

    float startRotate_;
    float endRotate_;
    float shootTime_;
    float stopTime_;

public:
    Laser();
    
    std::string getTypeId() override;

    // Set this laser's angle, in degrees (0 is right, increases clockwise)
    void setDirection(float angle);

    // Set the bounding angles for this laser's rotation
    void setRotate(float startRotate, float endRotate);

    void setShootTime(float shootTime);

    void setStopTime(float stopTime);

    //rotate the device
    void rotate(float angle);

    //void alertEnemy();

    //check if the device is hacked by the player
    bool isHacked();
    static const float COLLISION_SIZE;
};

#endif //LASER_HPP
