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