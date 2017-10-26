//
// Created by Ruoying Hao on 10/12/17.
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entities/Entity.hpp"

class Character:public Entity{
public:
	Character();

	void setVel(sf::Vector2f vel);
};

#endif // CHARACTER_HPP
