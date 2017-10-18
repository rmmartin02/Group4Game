#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"

class MenuScreen : public Screen {
public:
	MenuScreen();
	void render(sf::RenderWindow *window) override;
	void interpretInput() override;

private:

	void startGame();
	void loadLevel();
	void exitGame();
	sf::Texture background;
	sf::Sprite bg;
	sf::Sprite logo_sprite;
	sf::Texture logo;
	sf::Font taglineFont;
	sf::Text tagline;
	sf::RectangleShape start;
};

#endif // MENUSCREEN_HPP

