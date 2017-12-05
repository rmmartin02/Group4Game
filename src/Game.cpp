//
// Created by Ruoying Hao on 10/17/17.
//

#include "Game.hpp"

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Agent P: Infiltration");
    logic = new Logic();
    screenManager = new ScreenManager(logic);
    miniGameSong.openFromFile("../resource/minigamesong.wav");
}

Game::~Game()
{
}

void Game::initialize() {
    // if it can fail, or takes a long time, it shouldn't be in a constructor
    logic->load("../resource/maps/Map1.csv", "../resource/EntityLevel1.txt");
    screenManager->loadTextures();
}

void Game::Loop() {
    sf::Clock clock;
    //window->clear();
    while (window->isOpen()) {
        if (!miniGameSongStarted) {
            miniGameSong.setLoop(true);
            miniGameSong.play();
            miniGameSongStarted = true;
        }
 
        float deltaTime = clock.getElapsedTime().asSeconds();
        if (deltaTime >= 1.0f / 60.0f) {
            // process events
            sf::Event event;
            
            std::vector<sf::Event> events;
            while (window->pollEvent(event)) {
                // Exit
                if (event.type == sf::Event::Closed)
                    window->close();

                if (event.type == sf::Event::KeyPressed){
                    if (event.key.code == sf::Keyboard::Escape){
                        window->close();
                    }
                }
                
                events.push_back(event);
            }
            
            // Pass events to screen manager
            screenManager->interpretInput(events);
            
            //Don't really like this
            if (screenManager->isOnGameScreen()){
                logic->update(deltaTime);
                if(logic->getTimeLeft()<=0){

                    screenManager->switchToTimeout(window);
                }

            }
            if (screenManager->isOnMinigameScreen()){

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    static_cast<MiniGameScreen*>(screenManager->current_screen)->moveOnClick(
                            static_cast<MiniGameScreen*>(screenManager->current_screen)->shuffledPuzzle, sf::Vector2f(sf::Mouse::getPosition(*window)), window);
            }
            
            screenManager->render(window);
            //window->display();

            clock.restart();
        }
    }
}
