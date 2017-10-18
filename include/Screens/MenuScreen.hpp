#include "global.hpp"
#include "DEFINITION.hpp"
//#include "Screens/Screen.hpp"

class MenuScreen final: public Screen{
public:
	MenuScreen();
	void render() override;
	void interpretInput() override;

private:

	void startGame();
	void loadLevel();
	void exitGame();
};
