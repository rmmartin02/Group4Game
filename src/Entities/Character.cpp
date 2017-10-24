//
// Created by Ruoying Hao on 10/12/17.
//

#include "Entities/Character.hpp"

Character::Character(){
	sf::Texture texture;
	//load texture and sprite
	if (!texture.create(100, 100))
	{
    // error...
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(0, 255, 0));
	this->setSprite(sprite);
}