#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screens/Screen.hpp"
#include "Screens/GameScreen.hpp"
#include "Screens/MenuScreen.hpp"
#include "Screens/LoadingScreen.hpp"
#include "Screens/ControlsScreen.hpp"
#include "Screens/TimeoutScreen.hpp"

class ScreenManager{

public:

    ScreenManager(Logic *logic);

    void render(sf::RenderWindow *window);
    void interpretInput(std::vector<sf::Event>& events);

    bool loadTextures();
    bool isOnGameScreen();

private:
    Screen *current_screen;
    MenuScreen *menu_screen;
    GameScreen *game_screen;
    ControlsScreen *controls_screen;
    TimeoutScreen *timeout_screen;
    Logic* logic_;
};

#endif // SCREENMANAGER_HPP

