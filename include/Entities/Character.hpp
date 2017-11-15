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

	void setVel(sf::Vector2f vel);
    
    
    
private:
    // The maximum speed at which the character can move.
    static const float MAX_SPEED;

    // The radius of the character collision circle
    static const float COLLISION_SIZE;

};

#endif // CHARACTER_HPP
