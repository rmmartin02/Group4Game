#ifndef CONTROLSSCREEN_HPP
#define CONTROLSSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"
#include <cmath>

class ControlsScreen : public Screen {
public:
	ControlsScreen();
	void render(sf::RenderWindow *window) override;
	void interpretInput(sf::Event event) override;

private:
	sf::Texture background;
	sf::Sprite bg;
	sf::Sprite logo_sprite;
	sf::Texture logo;
	sf::Font textFont;
	sf::Text tagline;
	sf::Text back;

	sf::Text upText;
	sf::Text downText;
	sf::Text rightText;
	sf::Text leftText;

	sf::Text* controlOptions[4];
	int highlighted = 0;

	//sf::RectangleShape back;
};

#endif // CONTROLSSCREEN_HPP

