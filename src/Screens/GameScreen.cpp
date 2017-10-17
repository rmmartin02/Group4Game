#include "global.h"
#include "Screen.h"

class GameScreen final: public Screen{
public:
	GameScreeen();
	void render() override;
	void interpretInput() override;
private:
	void renderEntities();
};
