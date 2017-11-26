//
// Created by Ruoying Hao on 10/12/17.
//

#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include "Entities/Entity.hpp"

class Enemy1 : public Entity{
public:
    enemy1();
    isHacked();
    sf::Vector2f getStartPos();
    sf::Vector2f getDestination();
    //part of path finding, find the next position that the entity should go to
    sf::Vector2f getNextPos();

private:
    bool hacked;
    sf::Vector2f start_pos;
    sf::Vector2f dest_pos;
    static const float MOVE_SPEED;

};
#endif // ENEMY_HPP
