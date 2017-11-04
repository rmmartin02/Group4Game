//
// Created by Ruoying Hao on 10/31/17.
//

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Global.hpp"

// This class represents all detection devices
//camera and laser are child class of this super class
class Device {

public:
    Device();
    ~Device();

    //update
    virtual void update(float delta, int &logic);

    //Renders the device on window using sprite_
    void render (sf::RenderWindow *window);

    // Return the current position
    sf::Vector2f getPos();

    // Place the device at a new position
    void setPos(sf::Vector2f pos);

    //rotate the device
    void rotate(float angle);

    void alertEnemy();

    //check if the device is hacked by the player
    bool isHacked();

    void setSprite(sf::Sprite sprite);


protected:
    sf::Vector2f pos_;
    bool hacked;
    sf::Sprite sprite_;
};

#endif //DEVICE_HPP
