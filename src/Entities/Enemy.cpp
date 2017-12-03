//
// Created by Ruoying Hao on 11/25/17.
//

#include "Entities/Enemy.hpp"
const float Enemy::COLLISION_SIZE = 32.0f;
Enemy::Enemy(){
    sf::Texture texture;
    if (!texture.create(32, 32))
    {
        // error...
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(0, 255, 250));
    this->setSprite(sprite);

    b2CircleShape* collider = new b2CircleShape();
    collider->m_p.Set(0.0f, 0.0f);
    collider->m_radius = COLLISION_SIZE;
    this->attachShape(collider);

    hacked_=false;
    alerted_ = false;
    //change based on level?
    sight_distance_ = 100;
    //half
    sight_angle_ = 15;
    alert_time_ = 10;
    alert_time_left_ = 10;
    alert_radius_ = 100;
}

bool Enemy::isHacked(){
    return hacked_;
}

bool Enemy::isAlerted(){
    return alerted_;
}

void Enemy::setStartPos(sf::Vector2f pos){
    start_pos_=pos;

}

void Enemy::setDestPos(sf::Vector2f pos){
    dest_pos_=pos;

}

float Enemy::getAttackRadius(){
    return attack_radius_;
}

sf::Vector2f Enemy::getStartPos(){
    return start_pos_;
}

sf::Vector2f Enemy::getDestPos(){
    return dest_pos_;
}

sf::Vector2f Enemy::getNextPos(){

}


bool Enemy::canSeePlayer(sf::Vector2f character){
    sf::Vector2f u = sf::Vector2f(character.x-getPos().x,character.y-getPos().y);
    sf::Vector2f v = sf::Vector2f(sight_distance_*cos(vecutil::degToRad(getDirection())),
        sight_distance_*sin(vecutil::degToRad(getDirection())));
    sf::Vector2f e1 = sf::Vector2f(sight_distance_*cos(vecutil::degToRad(getDirection()-sight_angle_)),
        sight_distance_*sin(vecutil::degToRad(getDirection()-sight_angle_)));
    sf::Vector2f e2 = sf::Vector2f(sight_distance_*cos(getDirection()+sight_angle_),
        sight_distance_*sin(getDirection()+sight_angle_));
    if(vecutil::dotProd(u,v)>0){
        if(vecutil::dotProd(u,u)<(sight_distance_*sight_distance_)){
            if(vecutil::crossProd(e1,u)*vecutil::crossProd(u,e2)>=0.0f){
                return true;
            }
        }
    }
    return false;
}

void Enemy::alert(){
    //if enemy is hacked it can't alert/be alerted?
    alerted_ = true;
    alert_time_left_ = alert_time_;
}

void Enemy::signal(std::map<std::string, std::unique_ptr<Entity>> &entities){
    //alert enemies within radius
    for ( auto& pair : entities ) {
        Entity& e = *(pair.second.get());
        if (Enemy* enemy = dynamic_cast<Enemy*>(&e)){
            float dist = sqrt(pow(getPos().x-enemy->getPos().x,2)+pow(getPos().y-enemy->getPos().y,2));
            if (dist<alert_radius_){
                enemy->alert();
            }
        }
    }
}

void Enemy::attack(){
//switch to minigame screen

//if player fails minigame, damage?
//else player wins minigame, enemy hacked
}

void Enemy::timer(float deltaTime){
    alert_time_left_-=deltaTime;
    if(alert_time_left_<=0){
        alerted_ = false;
    }
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