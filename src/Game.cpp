//
// Created by Ruoying Hao on 10/17/17.
//

#include "Game.hpp"

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Agent P: Infiltration");
    menuScreen = MenuScreen();

}

Game::~Game()
{
}

void Game::Loop() {
    window->clear();
    while (window->isOpen()) {
        // process events
        sf::Event Event;
        while (window->pollEvent(Event)) {
            // Exit
            if (Event.type == sf::Event::Closed)
                window->close();
        }

        menuScreen.render(window);

    }
}
