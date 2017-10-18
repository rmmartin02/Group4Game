#include "global.hpp"
#include "DEFINITION.hpp"
//#include "Screens/Screen.hpp"

//class MenuScreen final: public Screen{
class MenuScreen{
public:
	MenuScreen();
	void render(sf::RenderWindow window) override;
	void interpretInput() override;

private:

	void startGame();
	void loadLevel();
	void exitGame();
};
