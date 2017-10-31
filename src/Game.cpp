//
// Created by Ruoying Hao on 10/17/17.
//

#include "Game.hpp"

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Agent P: Infiltration");
    logic = new Logic();
    screenManager = new ScreenManager(logic);
}

Game::~Game()
{
}

void Game::initialize() {
    // if it can fail, or takes a long time, it shouldn't be in a constructor
    logic->load("../resource/maps/MapLevel1Merge.csv");
    screenManager->loadTextures();
}

void Game::Loop() {
    sf::Clock clock;
    //window->clear();
    while (window->isOpen()) {
 
        float deltaTime = clock.getElapsedTime().asSeconds();
        if (deltaTime >= 1.0f / 60.0f) {
            // process events
            sf::Event Event;

            while (window->pollEvent(Event)) {
                // Exit
                if (Event.type == sf::Event::Closed)
                    window->close();

                if (Event.type == sf::Event::KeyPressed){
                    if (Event.key.code == sf::Keyboard::Escape){
                        window->close();
                    }
/*
                    if (currentScreen == menuScreen){
                        if (Event.key.code == sf::Keyboard::S)
                            currentScreen = gameScreen;
                    }
*/
                    
                }
            }
/*            
            if(currentScreen == gameScreen){
                sf::Vector2f cam_offset(0,0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    logic->moveCharacter(1);
                    //cam_offset.y -= CAMERA_SPEED * deltaTime;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    logic->moveCharacter(0);
                    //cam_offset.y += CAMERA_SPEED * deltaTime;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    logic->moveCharacter(2);
                    //cam_offset.x += CAMERA_SPEED * deltaTime;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    logic->moveCharacter(3);
                    //cam_offset.x -= CAMERA_SPEED * deltaTime;
                }
                logic->update(deltaTime);
                gameScreen->centerCameraOnCharacter(window);
            }
 */     
            screenManager->render(window);
            //window->display();

            clock.restart();
        }
    }
}
