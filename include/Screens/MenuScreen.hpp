#include "global.h"
#include "Screen.h"

class MenuScreen final: public Screen{
public:
	MenuScreeen();
	void render() override;
	void interpretInput() override;
private:
	void startGame();
	void loadLevel();
	void exitGame();
};
