//
// Created by Ruoying Hao on 10/12/17.
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"

class Character : public Entity{
public:
    // The rate at which the character accelerates
    static const float ACCELERATION;
    
    Character();

    // Change the velocity according to an inputted movement direction
    void onMoveInput(sf::Vector2f);
    
    // Handle this character's collision with a wall shape
    void onWallCollision(sf::Vector2f point, sf::Vector2f normal) override;
    
private:
    // The maximum speed at which the character can move.
    static const float MAX_SPEED;

    // The radius of the character collision circle
    static const float COLLISION_SIZE;

};

#endif // CHARACTER_HPP
