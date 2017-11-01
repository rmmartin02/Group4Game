#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screens/Screen.hpp"
#include "Screens/GameScreen.hpp"
#include "Screens/MenuScreen.hpp"
#include "Screens/LoadingScreen.hpp"

class ScreenManager{

public:

    ScreenManager(Logic *logic);

    void render(sf::RenderWindow *window);
    void interpretInput(sf::Event Event);

    bool loadTextures();

    bool isOnGameScreen();

private:

    Screen *currentScreen;
    MenuScreen *menuScreen;
    GameScreen *gameScreen;
    Logic* logic_;
};

#endif // SCREENMANAGER_HPP

