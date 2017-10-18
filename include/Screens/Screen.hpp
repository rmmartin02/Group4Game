#include "global.hpp"

class Screen {
public:
	Screen();
	void update(const sf::Time& frameTime);
	virtual void render()=0;
	virtual void interpretInput()=0;
};
