//
// Created by Ruoying Hao on 10/17/17.
//

#ifndef CSCI437_GAME_HPP
#define CSCI437_GAME_HPP

#endif //CSCI437_GAME_HPP
#include "Global.hpp"
#include "Screens/MenuScreen.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Loop();

private:
    sf::RenderWindow *window;
    MenuScreen menuScreen;

};