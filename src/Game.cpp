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
    
    level_manager_.addLevel("Level 1", "../resource/maps/Map1.csv", "../resource/EntityLevel1.txt");
    level_manager_.addLevel("Level 2", "../resource/maps/Map2.csv", "../resource/EntityLevel1.txt");

    //logic->load("Level 1", "../resource/maps/Map1.csv", "../resource/EntityLevel1.txt", 10 * 60);
    
    logic->load(level_manager_.getCurrentLevelName(),
                level_manager_.getCurrentTileFilename(),
                level_manager_.getCurrentEntityFilename(),
                10);
    screenManager->loadTextures();
}

void Game::Loop() {
    sf::Clock clock;
    //window->clear();
    while (window->isOpen()) {
 
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
            
            if (screenManager->isOnGameScreen()){
                //std::cout << "Logic update " << std::endl;
                logic->update(deltaTime);
                switch( logic->getPlayState() ) {
                    case Logic::PlayState::LOST:
                        screenManager->switchToTimeout(window);
                        break;
                    case Logic::PlayState::WON:
                        std::cout << "Game.cpp: detected game logic WON state" << std::endl;
                        // switch to intermediate / loading screen
                        // TODO; make this a win instead of a timeout
                        screenManager->switchToTimeout(window);
                        std::cout << "Game.cpp: switched to timeout?" << std::endl;
                        
                        // if we have another level
                        if (level_manager_.nextLevel()) {
                            // then have logic load the next level
                            logic->load(level_manager_.getCurrentLevelName(),
                                        level_manager_.getCurrentTileFilename(),
                                        level_manager_.getCurrentEntityFilename(),
                                        logic->getTimeLeft());
                            std::cout << "Game.cpp: next level loaded." << std::endl;
                        }
                        else {
                            // switch to the final hacking challenge, or an intermediate screen that introduces it
                            // SWITCHEROO
                        }
                        
                        break;
                    default:
                        break;
                }
            }
            
            screenManager->render(window);
            //window->display();

            clock.restart();
        }
    }
}
