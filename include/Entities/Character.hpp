//
// Created by Ruoying Hao on 10/12/17.
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"

class Character : public Entity{
public:
	Character();

	void setVel(sf::Vector2f vel);
    
    // Handle this character's collision with a wall shape
    void onWallCollision(b2Vec2 point, b2Vec2 normal) override;
    
private:
    // The maximum speed at which the character can move.
    static const float MAX_SPEED;

    // The radius of the character collision circle
    static const float COLLISION_SIZE;

};

#endif // CHARACTER_HPP
