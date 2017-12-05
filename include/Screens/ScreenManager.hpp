#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screens/Screen.hpp"
#include "Screens/GameScreen.hpp"
#include "Screens/MenuScreen.hpp"
#include "Screens/LoadingScreen.hpp"
#include "Screens/ControlsScreen.hpp"
#include "Screens/MiniGameScreen.hpp"
#include "Screens/TimeoutScreen.hpp"
#include "Screens/InfoScreen.hpp"

class ScreenManager{

public:

    ScreenManager(Logic *logic);

    void render(sf::RenderWindow *window);
    void interpretInput(std::vector<sf::Event>& events);
    void switchToTimeout(sf::RenderWindow *window);
    void switchToMinigame(sf::RenderWindow *window);

    bool loadTextures();
    bool isOnGameScreen();
    bool isOnMinigameScreen();

    Screen *current_screen;

private:
    //Screen *current_screen;
    MenuScreen *menu_screen;
    GameScreen *game_screen;
    ControlsScreen *controls_screen;
    TimeoutScreen *timeout_screen;
    MiniGameScreen *minigame_screen;
    InfoScreen *info_screen;
    Logic* logic_;
    sf::RenderWindow* window;
};

#endif // SCREENMANAGER_HPP

