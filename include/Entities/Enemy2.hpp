//
// Created by Ruoying Hao on 11/25/17.
//

#ifndef ENEMY2_HPP
#define ENEMY2_HPP
#include "Entities/Entity.hpp"
class Enemy2 : public Entity{
public:
    Enemy2();
    bool isHacked();
    sf::Vector2f getStartPos();
    sf::Vector2f getDestination();

    sf::Vector2f getNextPos();
private:
    bool hacked;
    sf::Vector2f start_pos;
    sf::Vector2f dest_pos;
    static const float MOVE_SPEED;


};
#endif //ENEMY2_HPP
