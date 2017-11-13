//
// Created by Ruoying Hao on 10/31/17.
//

#ifndef LASER_HPP
#define LASER_HPP

#include "Global.hpp"

class Laser {

protected:
    sf::Vector2f pos_;
    bool hacked;
    sf::Sprite sprite_;
    int dir_;
    float startRotate_;
    float endRotate_;
    float shootTime_;
    float stopTime_;

public:
    Laser();

    //update
    virtual void update(float delta, int &logic);

    //Renders the device on window using sprite_
    void render (sf::RenderWindow *window);

    // Return the current position
    sf::Vector2f getPos();

    //return direction: 0,1,2,3 -> NORTH,EAST,SOUTH,WEST
    int getDirection();

    // Place the device at a new position
    void setPos(sf::Vector2f pos);

    void setRotate(float startRotate, float endRotate);

    void setShootTime(float shootTime);

    void setStopTime(float stopTime);

    void setDirection(int dir);

    //rotate the device
    void rotate(float angle);

    //void alertEnemy();

    //check if the device is hacked by the player
    bool isHacked();

    void setTexture(sf::Texture tex);
    void setSprite(sf::Sprite sprite);
};

#endif //LASER_HPP
