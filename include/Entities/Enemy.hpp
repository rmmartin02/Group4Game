//
// Created by Ruoying Hao on 10/12/17.
//

#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include "Entities/Entity.hpp"
#include "VecUtil.hpp"

#include <map>
#include <deque>

class Enemy : public Entity{
public:
    Enemy();
    bool isHacked();
    bool isAlerted();
    void setStartPos(sf::Vector2f pos);
    void setDestPos(sf::Vector2f pos);
    void setPatrolPath(std::deque<sf::Vector2f> path);
    std::deque<sf::Vector2f> getPatrolPath();
    sf::Vector2f getStartPos();
    sf::Vector2f getDestPos();
    //part of path finding, find the next position that the entity should go to
    sf::Vector2f getNextPos();
    static const float COLLISION_SIZE;

    bool canSeePlayer(sf::Vector2f character);
    void alert();
    void signal(std::map<std::string, std::unique_ptr<Entity>> &entities);
    void timer(float deltaTime);
    float getAttackRadius();
    void attack();

private:
    bool hacked_;
    bool alerted_;
    sf::Vector2f start_pos_;
    sf::Vector2f dest_pos_;
    static const float MOVE_SPEED;

    
    float sight_distance_;
    float sight_angle_;
    float alert_time_;
    float alert_time_left_ ;
    float alert_radius_;
    float attack_radius_;

    std::deque<sf::Vector2f> patrolPath_;
};
#endif // ENEMY_HPP
