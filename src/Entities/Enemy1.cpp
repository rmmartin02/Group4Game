//
// Created by Ruoying Hao on 11/25/17.
//

#include "Entities/Enemy1.hpp"
#include "VecUtil.hpp"
const float Enemy1::COLLISION_SIZE = 32.0f;
Enemy1::Enemy1(){
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

    hacked=false;

}

bool Enemy1::isHacked(){
    return hacked;
}

void Enemy1::setStartPos(sf::Vector2f pos){
    start_pos_=pos;

}

void Enemy1::setDestPos(sf::Vector2f pos){
    dest_pos_=pos;

}

sf::Vector2f Enemy1::getStartPos(){
    return start_pos_;
}

sf::Vector2f Enemy1::getDestPos(){
    return dest_pos_;
}

sf::Vector2f getNextPos(){

}