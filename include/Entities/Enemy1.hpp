//
// Created by Ruoying Hao on 10/12/17.
//

#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include "Entities/Entity.hpp"

class Enemy1 : public Entity{
public:
    Enemy1();
    bool isHacked();
    void setStartPos(sf::Vector2f pos);
    void setDestPos(sf::Vector2f pos);
    sf::Vector2f getStartPos();
    sf::Vector2f getDestPos();
    //part of path finding, find the next position that the entity should go to
    sf::Vector2f getNextPos();
    static const float COLLISION_SIZE;

private:
    bool hacked;
    sf::Vector2f start_pos_;
    sf::Vector2f dest_pos_;
    static const float MOVE_SPEED;

};
#endif // ENEMY_HPP
