//
// Created by Ruoying Hao on 10/17/17.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "Global.hpp"
#include "Logic.hpp"
#include "Screens/MenuScreen.hpp"
#include "Screens/GameScreen.hpp"

class Game
{
public:
    Game();
    ~Game();
    
    void initialize();

    void Loop();


private:
    sf::RenderWindow *window;
    Logic *logic;
    Screen *currentScreen;
    MenuScreen *menuScreen;
    GameScreen *gameScreen;
};

#endif // GAME_HPP

