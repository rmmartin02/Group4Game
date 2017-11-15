#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Global.hpp"

class Screen {
public:
    virtual void render(sf::RenderWindow * window) = 0;
    virtual void interpretInput(std::vector<sf::Event>& events) = 0;
};

#endif // SCREEN_HPP

