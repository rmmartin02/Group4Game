#ifndef CONTROLSSCREEN_HPP
#define CONTROLSSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"

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
	sf::Text start;
	//sf::RectangleShape start;
};

#endif // CONTROLSSCREEN_HPP

