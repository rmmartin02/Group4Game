#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Global.hpp"

class Screen {
public:
	//Screen();
	//void update(const sf::Time& frameTime);
	virtual void render(sf::RenderWindow * window) = 0;
	virtual void interpretInput(sf::Event event) = 0;
};

#endif // SCREEN_HPP

