//
// Created by Ruoying Hao on 10/17/17.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "Global.hpp"
#include "Logic.hpp"
#include "Screens/MenuScreen.hpp"
#include "Screens/GameScreen.hpp"
#include "Screens/MiniGameScreen.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Loop();


private:
    sf::RenderWindow *window;
    Logic *logic;
    Screen *currentScreen;
    MenuScreen *menuScreen;
    GameScreen *gameScreen;
    MiniGameScreen *miniGameScreen;

    bool miniGameSongStarted = false;

    sf::Music miniGameSong;
};

#endif // GAME_HPP

