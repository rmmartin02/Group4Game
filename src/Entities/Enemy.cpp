//
// Created by Ruoying Hao on 11/25/17.
//

#include "Entities/Enemy.hpp"
#include "VecUtil.hpp"
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

}

void Enemy::update(float delta, int &logic){

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

bool Enemy::canSeePlayer(sf::Vector2f character){
    float dist = sqrt(pow(pos_.x-character.x,2)+pow(pos_.y-character.y,2));
    if(dist<=sight_distance_){
        std::cout << "LOS: In distance\n";
        float x3 = pos_.x+vel_.x;
        float y3 = pos_.y+vel_.y;
        float a = pow(pos_.x-character.x,2)+pow(pos_.y-character.y,2);
        float b = pow(pos_.x-x3,2)+pow(pos_.y-y3,2);
        float c = pow(x3-character.x,2)+pow(y3-character.x,2);
        float angle = acos((a+b-c)/sqrt(4*a*b));
        if(angle<=sight_angle_){
            std::cout << "LOS: In Angle\n";
            //still need to write a check for walls here
            return true;
        }
    }
    return false;
}