//
// Created by Ruoying Hao on 11/25/17.
//

#include "Entities/Enemy.hpp"
const float Enemy::COLLISION_SIZE = 32.0f;
Enemy::Enemy(){
    b2CircleShape* collider = new b2CircleShape();
    collider->m_p.Set(0.0f, 0.0f);
    collider->m_radius = COLLISION_SIZE;
    this->attachShape(collider);

    is_level_2_ = false;
    hacked_=false;
    alerted_ = false;
    off_patrol = false;
    has_path_back_= false;
    has_chase_path_ = false;
    //change based on level?
    attack_radius_ = 1*32;
    move_speed_ = 1;
    sight_distance_ = 5*32;
    //half
    sight_angle_ = 15;
    alert_time_ = 10;
    alert_time_left_ = 10;
    alert_radius_ = 5*32;
    attack_radius_=44;

    cur_patrol_node = 1;
    cur_patrol_path = 0;
    cur_chase_node = 1;

    last_known_character_pos_ = sf::Vector2f(0,0);
}

Enemy::Enemy(bool isLevel2){
    b2CircleShape* collider = new b2CircleShape();
    collider->m_p.Set(0.0f, 0.0f);
    collider->m_radius = COLLISION_SIZE;
    this->attachShape(collider);

    hacked_=false;
    alerted_ = false;
    off_patrol = false;
    has_path_back_= false;
    has_chase_path_ = false;
    if(isLevel2){
        attack_radius_ = 1.5*32;
        is_level_2_ = true;
        move_speed_ = 1.5;
        sight_distance_ = 5*32;
        attack_radius_ = 1.5*32;
        //half
        sight_angle_ = 40;
        alert_time_ = 10;
        alert_time_left_ = 10;
        alert_radius_ = 5*32;
        attack_radius_=44;
    }
    else{
        attack_radius_ = 1*32;
        is_level_2_ = false;
        move_speed_ = 1;
        sight_distance_ = 4*32;
        //half
        sight_angle_ = 30;
        alert_time_ = 7.5;
        alert_time_left_ = 7.5;

        sight_angle_ = 15;
        alert_time_ = 10;
        alert_time_left_ = 10;
        alert_radius_ = 5*32;
        attack_radius_=44;
    }
    cur_patrol_node = 1;
    cur_patrol_path = 0;
    cur_chase_node = 1;

    last_known_character_pos_ = sf::Vector2f(0,0);
}

std::string Enemy::getTypeId() {
    if(is_level_2_){
        return Entity::ENEMY2_ID;
    }
    return Entity::ENEMY1_ID;
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

float Enemy::getAttackRadius(){
    //std::cout<<"Enemy::attack radius "<<attack_radius_<<"\n";
    return attack_radius_;
}


sf::Vector2f Enemy::getCurrentPatrolNode(){
    return patrol_paths_.at(cur_patrol_path).at(cur_patrol_node);
}

//https://legends2k.github.io/2d-fov/design.html
bool Enemy::canSeePlayer(sf::Vector2f character){
    character = sf::Vector2f(character.x-16.0f, character.y-16.0f);
    sf::Vector2f u = sf::Vector2f(character.x-getCenterPos().x,character.y-getCenterPos().y);
    sf::Vector2f v = vecutil::fromPolar(sight_distance_,vecutil::degToRad(getDirection()));
    sf::Vector2f e1 = vecutil::fromPolar(sight_distance_,vecutil::degToRad(getDirection()+sight_angle_));
    sf::Vector2f e2 = vecutil::fromPolar(sight_distance_,vecutil::degToRad(getDirection()-sight_angle_));
    if(vecutil::dotProd(u,v)<=0){
        return false;
    }
    if(vecutil::dotProd(u,u)>(sight_distance_*sight_distance_)){
        return false;
    }
    if(vecutil::crossProd(e1,u)*vecutil::crossProd(u,e2)>=0.0f){
        return true;
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
    sf::Texture texture;
    if (!texture.create(32, 32))
    {
        // error...
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255, 0, 0));
    sprite_ = sprite;
}

void Enemy::unAlert(){
    alerted_ = false;
    off_patrol = true;
    has_path_back_= false;
    has_chase_path_ = false;
    sf::Texture texture;
    if (!texture.create(32, 32))
    {
        // error...
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(0, 255, 250));
    sprite_ = sprite;
}

void Enemy::signal(std::map<std::string, std::unique_ptr<Entity>> &entities){
    //alert enemies within radius
    //std::cout << "Signal\n";
    for ( auto& pair : entities ) {
        Entity& e = *(pair.second.get());
        if (Enemy* enemy = dynamic_cast<Enemy*>(&e)){
            float dist = sqrt(pow(getPos().x-enemy->getPos().x,2)+pow(getPos().y-enemy->getPos().y,2));
            if (dist<alert_radius_){
                //std::cout << "Signal Alert\n";
                enemy->alert();
            }
        }
    }
}

void Enemy::attack(){
//switch to minigame screen
    std::cout << "attack\n";
    hacked_ = true;
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

void Enemy::setPatrolPath(std::vector<std::deque<sf::Vector2f>> paths){
    patrol_paths_.clear();
    patrol_paths_.shrink_to_fit();
    for(int i = 0; i<paths.size(); i++){
        for(int j = 0; j<paths.at(i).size();j++){ 
            std::cout << paths.at(i).at(j).x << " " << paths.at(i).at(j).y << "\n";
        }
    }
    patrol_paths_=paths;
    paths.clear();
    paths.shrink_to_fit();
}

std::vector<std::deque<sf::Vector2f>> Enemy::getPatrolPath(){
    return patrol_paths_;
}

void Enemy::setChasePath(std::deque<sf::Vector2f> path){
    has_chase_path_ = true;
    cur_chase_node = 1;
    chase_path_.clear();
    chase_path_.shrink_to_fit();
    chase_path_=path;
    path.clear();
    path.shrink_to_fit();
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
    return_path_.clear();
    return_path_.shrink_to_fit();
    return_path_=path;
    path.clear();
    path.shrink_to_fit();
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
    if(vecutil::distance(patrol_paths_.at(cur_patrol_path).at(cur_patrol_node),getPos())<1){
        cur_patrol_node += 1;
        if(cur_patrol_node == patrol_paths_.at(cur_patrol_path).size()){
            //std::cout << "Reset node\n";
            cur_patrol_node = 1;
            cur_patrol_path += 1;
            if(cur_patrol_path == patrol_paths_.size()){
                //std::cout << "Reset path\n";
                cur_patrol_path = 0;
            }
        }
        //std::cout << cur_patrol_node << " " << cur_patrol_path << "\n";
    }
    sf::Vector2f curNode = patrol_paths_.at(cur_patrol_path).at(cur_patrol_node);
    sf::Vector2f dirVec = sf::Vector2f(curNode.x-getPos().x,curNode.y-getPos().y);
    sf::Vector2f velVec = move_speed_ * (dirVec/vecutil::length(dirVec));
    deliberateMotion(velVec);
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
    if(vecutil::distance(curNode,getPos())<1 && cur_chase_node<chase_path_.size()-1){
        cur_chase_node += 1;
    }
    if(cur_chase_node<=chase_path_.size()-1){
        curNode = chase_path_.at(cur_chase_node);
        sf::Vector2f dirVec = sf::Vector2f(curNode.x-getPos().x,curNode.y-getPos().y);
        sf::Vector2f velVec = move_speed_ * (dirVec/vecutil::length(dirVec));
        deliberateMotion(velVec);
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
    if(vecutil::distance(curNode,getPos())<1){
        cur_return_node += 1;
    }
    if(cur_return_node<=return_path_.size()-1){
        curNode = return_path_.at(cur_return_node);
        sf::Vector2f dirVec = sf::Vector2f(curNode.x-getPos().x,curNode.y-getPos().y);
        sf::Vector2f velVec = move_speed_ * (dirVec/vecutil::length(dirVec));
        deliberateMotion(velVec);
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
