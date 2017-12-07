//
// Created by Ruoying Hao on 10/17/17.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "Global.hpp"
#include "Logic.hpp"
#include "Screens/ScreenManager.hpp"
#include "LevelManager.hpp"

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
    ScreenManager *screenManager;
    
    LevelManager level_manager_;
    bool miniGameSongStarted=false;
    sf::Music miniGameSong;
};

#endif // GAME_HPP

