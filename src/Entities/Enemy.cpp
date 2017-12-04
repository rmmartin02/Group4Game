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
    off_patrol = false;
    has_path_back_= false;
    has_chase_path_ = false;
    //change based on level?
    move_speed_ = 1;
    sight_distance_ = 5*32;
    //half
    sight_angle_ = 15;
    alert_time_ = 10;
    alert_time_left_ = 10;
    alert_radius_ = 2*32;

    cur_patrol_node = 1;
    cur_patrol_dir = 1;
    cur_chase_node = 1;

    last_known_character_pos_ = sf::Vector2f(0,0);
}

bool Enemy::isHacked(){
    return hacked_;
}

bool Enemy::isAlerted(){
    return alerted_;
}

bool Enemy::isOffPatrol(){
    return off_patrol;
}

bool Enemy::hasPathBack(){
    return has_path_back_;
}

bool Enemy::hasChasePath(){
    return has_chase_path_;
}

void Enemy::setPathBackTrue(){
    has_path_back_ = true;
}

/*
void Enemy::setStartPos(sf::Vector2f pos){
    start_pos_=pos;

}

void Enemy::setDestPos(sf::Vector2f pos){
    dest_pos_=pos;

}*/

float Enemy::getAttackRadius(){
    return attack_radius_;
}
/*
sf::Vector2f Enemy::getStartPos(){
    return start_pos_;
}

sf::Vector2f Enemy::getDestPos(){
    return dest_pos_;
}
*/
sf::Vector2f Enemy::getCurrentPatrolNode(){
    return patrol_path_.at(cur_patrol_node);
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
    off_patrol = true;
    has_path_back_= false;
    has_chase_path_ = false;
}

void Enemy::unAlert(){
    alerted_ = false;
    off_patrol = true;
    has_path_back_= false;
    has_chase_path_ = false;
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
    std::cout << "attack\n";
//if player fails minigame, damage?
//else player wins minigame, enemy hacked
}

void Enemy::timer(float deltaTime){
    alert_time_left_-=deltaTime;
    //std::cout << alert_time_left_ << "\n";
    if(alert_time_left_<=0){
        unAlert();
        std::cout << "Unalert\n";
    }
}

void Enemy::setPatrolPath(std::deque<sf::Vector2f> path){
//    patrolPath_.clear();
    patrol_path_=path;
}

std::deque<sf::Vector2f> Enemy::getPatrolPath(){
    /*for(int i=0;i<patrolPath_.size();i++){
        std::cout<<"Enemy.cpp:enemy path: "<<patrolPath_[i].x<<" "<<patrolPath_[i].y<<"\n";
    }
    std::cout<<"Enemy.cpp:enemy path inspect complete\n";*/
    return patrol_path_;
}

void Enemy::setChasePath(std::deque<sf::Vector2f> path){
    has_chase_path_ = true;
    cur_chase_node = 1;
    chase_path_=path;
}

bool Enemy::hasFinishedChase(){
    return cur_chase_node==chase_path_.size()-1;
}

sf::Vector2f Enemy::getChaseEndPos(){
    return chase_path_.at(chase_path_.size()-1);
}

std::deque<sf::Vector2f> Enemy::getChasePath(){
    return chase_path_;
}

void Enemy::setReturnPath(std::deque<sf::Vector2f> path){
    cur_return_node = 1;
    return_path_=path;
}

std::deque<sf::Vector2f> Enemy::getReturnPath(){
    return return_path_;
}

void Enemy::setLastKnownCharacterPos(sf::Vector2f pos){
    last_known_character_pos_ = pos;
}

sf::Vector2f Enemy::getLastKnownCharacterPos(){
    return last_known_character_pos_;
}

void Enemy::followPatrolPath(){
    sf::Vector2f curNode = patrol_path_.at(cur_patrol_node);
    if(vecutil::distance(curNode,getPos())<.5){
        cur_patrol_node += cur_patrol_dir;
        if (cur_patrol_node<0){
            std::cout << "Beginning of Patrol\n";
            cur_patrol_node = 1;
            cur_patrol_dir = 1;
        }
        if (cur_patrol_node>patrol_path_.size()-1){
            std::cout << "End of Patrol\n";
            cur_patrol_node = patrol_path_.size()-2;
            cur_patrol_dir = -1;
        }
        curNode = patrol_path_.at(cur_patrol_node);
    }
    sf::Vector2f dirVec = sf::Vector2f(curNode.x-getPos().x,curNode.y-getPos().y);
    sf::Vector2f velVec = move_speed_ * (dirVec/vecutil::length(dirVec));
    setVel(velVec);
    /*
    std::cout<< "CurPos: " << getPos().x << " " << getPos().y  << " " 
    << vecutil::distance(curNode,getPos()) <<" CurNode: " << cur_patrol_node 
    << "/" << patrol_path_.size()-1 << " " << curNode.x << " " << curNode.y << "\n";
    std::cout<< "Vel: " << velVec.x << " " << velVec.y << "\n";
    */
}

void Enemy::followChasePath(){
    sf::Vector2f dirVec;
    sf::Vector2f velVec;
    sf::Vector2f curNode = chase_path_.at(cur_chase_node);
    if(vecutil::distance(curNode,getPos())<.5 && cur_chase_node<chase_path_.size()-1){
        cur_chase_node += 1;
    }
    if(cur_chase_node<=chase_path_.size()-1){
        curNode = chase_path_.at(cur_chase_node);
        sf::Vector2f dirVec = sf::Vector2f(curNode.x-getPos().x,curNode.y-getPos().y);
        sf::Vector2f velVec = move_speed_ * (dirVec/vecutil::length(dirVec));
        setVel(velVec);
        /*
        std::cout<< "Chasing: CurPos: " << getPos().x << " " << getPos().y  << " " 
        << vecutil::distance(curNode,getPos()) <<" CurNode: " << cur_chase_node 
        << "/" << chase_path_.size()-1 << " " << curNode.x << " " << curNode.y << "\n";
        std::cout<< "Vel: " << velVec.x << " " << velVec.y << "\n";
        */

    }
}

void Enemy::followReturnPath(){
    sf::Vector2f dirVec;
    sf::Vector2f velVec;
    sf::Vector2f curNode = return_path_.at(cur_return_node);
    if(vecutil::distance(curNode,getPos())<.5){
        cur_return_node += 1;
    }
    if(cur_return_node<=return_path_.size()-1){
        curNode = return_path_.at(cur_return_node);
        sf::Vector2f dirVec = sf::Vector2f(curNode.x-getPos().x,curNode.y-getPos().y);
        sf::Vector2f velVec = move_speed_ * (dirVec/vecutil::length(dirVec));
        setVel(velVec);
        /*
        std::cout<< "Chasing: CurPos: " << getPos().x << " " << getPos().y  << " " 
        << vecutil::distance(curNode,getPos()) <<" CurNode: " << cur_return_node 
        << "/" << return_path_.size()-1 << " " << curNode.x << " " << curNode.y << "\n";
        std::cout<< "Vel: " << velVec.x << " " << velVec.y << "\n";
        */

    }
    else{
        off_patrol = false;
    }
    
}