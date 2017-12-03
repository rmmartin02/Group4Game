//
// Created by Ruoying Hao on 11/25/17.
//

#include "Entities/Enemy.hpp"
#include "VecUtil.hpp"
const float Enemy::COLLISION_SIZE = 32.0f;
Enemy::Enemy(){
    b2CircleShape* collider = new b2CircleShape();
    collider->m_p.Set(0.0f, 0.0f);
    collider->m_radius = COLLISION_SIZE;
    this->attachShape(collider);

    hacked_=false;

}

std::string Enemy::getTypeId() {
    return Entity::ENEMY_ID;
}

bool Enemy::isHacked(){
    return hacked_;
}

void Enemy::setStartPos(sf::Vector2f pos){
    start_pos_=pos;

}

void Enemy::setDestPos(sf::Vector2f pos){
    dest_pos_=pos;

}

sf::Vector2f Enemy::getStartPos(){
    return start_pos_;
}

sf::Vector2f Enemy::getDestPos(){
    return dest_pos_;
}

sf::Vector2f Enemy::getNextPos(){

}
void Enemy::setPatrolPath(std::deque<sf::Vector2f> path){
//    patrolPath_.clear();

    patrolPath_=path;

}
std::deque<sf::Vector2f> Enemy::getPatrolPath(){
    for(int i=0;i<patrolPath_.size();i++){
        std::cout<<"Enemy.cpp:enemy path: "<<patrolPath_[i].x<<" "<<patrolPath_[i].y<<"\n";
    }
    std::cout<<"Enemy.cpp:enemy path inspect complete\n";
    return patrolPath_;
}
