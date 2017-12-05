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
    
    std::string getTypeId() override;
    
    Enemy(bool isLevel2);
    bool isLevel2();
    bool isHacked();
    bool isAlerted();
    bool isOffPatrol();
    bool hasFinishedChase();
    bool hasPathBack();
    bool hasChasePath();
    //void setStartPos(sf::Vector2f pos);
    //void setDestPos(sf::Vector2f pos);
    void setPathBackTrue();
    void setLastKnownCharacterPos(sf::Vector2f pos);
    void setPatrolPath(std::vector<std::deque<sf::Vector2f>> paths);
    void setChasePath(std::deque<sf::Vector2f> path);
    void setReturnPath(std::deque<sf::Vector2f> path);
    std::deque<sf::Vector2f> getChasePath();
    std::vector<std::deque<sf::Vector2f>> getPatrolPath();
    std::deque<sf::Vector2f> getReturnPath();

    //follows currently set path from cur node to next node
    void followPatrolPath();
    void followChasePath();
    void followReturnPath();
    //sf::Vector2f getStartPos();
    //sf::Vector2f getDestPos();
    //part of path finding, find the next position that the entity should go to
    sf::Vector2f getCurrentPatrolNode();
    sf::Vector2f getLastKnownCharacterPos();
    sf::Vector2f getChaseEndPos();
    static const float COLLISION_SIZE;

    bool canSeePlayer(sf::Vector2f);
    void alert();
    void unAlert();
    void signal(std::map<std::string, std::unique_ptr<Entity>> &entities);
    void timer(float deltaTime);
    float getAttackRadius();
    void attack();

private:
    bool is_level_2_;
    bool hacked_;
    bool alerted_;
    bool off_patrol;
    bool has_path_back_;
    bool has_chase_path_;
    //sf::Vector2f start_pos_;
    //sf::Vector2f dest_pos_;
    
    float move_speed_;
    float sight_distance_;
    float sight_angle_;
    float alert_time_;
    float alert_time_left_ ;
    float alert_radius_;
    float attack_radius_;

    sf::Vector2f last_known_character_pos_;

    int cur_patrol_node;
    int cur_patrol_path;
    int cur_chase_node;
    int cur_return_node;
    std::vector<std::deque<sf::Vector2f>> patrol_paths_;
    std::deque<sf::Vector2f> chase_path_;
    std::deque<sf::Vector2f> return_path_;
};
#endif // ENEMY_HPP
