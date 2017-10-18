#include "Global.h"
#include "Screen.h"

class LoadingScreen final: public Screen{
public:
	LoadingScreeen();
	void render() override;
	void interpretInput() override;
private:
	void cancelLoad();
};
