//
// Created by Ruoying Hao on 10/17/17.
//

#include "Game.hpp"

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Agent P: Infiltration");
    menuScreen = new MenuScreen();
    logic = new Logic();
    gameScreen = new GameScreen(logic);

    gameScreen->loadTextures();
    currentScreen = menuScreen;
}

Game::~Game()
{
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
                    
                    if (currentScreen == menuScreen){
                        if (Event.key.code == sf::Keyboard::S)
                            currentScreen = gameScreen;
                    }

                    
                }
            }
            
            if(currentScreen == gameScreen){
                sf::Vector2f cam_offset(0,0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    cam_offset.y -= CAMERA_SPEED * deltaTime;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    cam_offset.y += CAMERA_SPEED * deltaTime;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    cam_offset.x += CAMERA_SPEED * deltaTime;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    cam_offset.x -= CAMERA_SPEED * deltaTime;
                }
                gameScreen->panCamera(window, cam_offset);
                logic->update(deltaTime);
            }
        
            currentScreen->render(window);
            //window->display();

            clock.restart();
        }
    }
}
