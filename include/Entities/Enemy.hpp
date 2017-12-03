//
// Created by Ruoying Hao on 10/12/17.
//

#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include "Entities/Entity.hpp"
#include <deque>

class Enemy : public Entity{
public:
    Enemy();
    
    std::string getTypeId() override;
    
    bool isHacked();
    void setStartPos(sf::Vector2f pos);
    void setDestPos(sf::Vector2f pos);
    void setPatrolPath(std::deque<sf::Vector2f> path);
    std::deque<sf::Vector2f> getPatrolPath();
    sf::Vector2f getStartPos();
    sf::Vector2f getDestPos();
    //part of path finding, find the next position that the entity should go to
    sf::Vector2f getNextPos();
    static const float COLLISION_SIZE;

private:
    bool hacked_;
    sf::Vector2f start_pos_;
    sf::Vector2f dest_pos_;
    static const float MOVE_SPEED;
    std::deque<sf::Vector2f> patrolPath_;

};
#endif // ENEMY_HPP
