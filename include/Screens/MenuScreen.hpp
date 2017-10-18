#include "Global.hpp"
//#include "Screens/Screen.hpp"

//class MenuScreen final: public Screen{
class MenuScreen{
public:
	MenuScreen();
	void render(sf::RenderWindow *window);
	void interpretInput();// override;

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
