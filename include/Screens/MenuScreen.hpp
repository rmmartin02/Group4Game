#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"

class MenuScreen : public Screen {
public:
	MenuScreen();
	void render(sf::RenderWindow *window) override;
	void interpretInput(sf::Event event) override;

	int getHighlighted();

private:

	void startGame();
	void loadLevel();
	void exitGame();
	sf::Texture background;
	sf::Sprite bg;
	sf::Sprite logo_sprite;
	sf::Texture logo;
	sf::Font textFont;
	sf::Text tagline;
	sf::Text start;
	sf::Text options;

	sf::Text* menu_options[2];
	int highlighted = 0;
	//sf::RectangleShape start;
};

#endif // MENUSCREEN_HPP

