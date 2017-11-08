//
// Created by Ruoying Hao on 10/31/17.
//

#include "Entities/Laser.hpp"

Laser::Laser(){
    sf::Texture texture;
    if (!texture.create(15, 15))
    {
        // error...
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(0, 200, 0));
    this->setSprite(sprite);
    std::cout << "Laser created";

}
