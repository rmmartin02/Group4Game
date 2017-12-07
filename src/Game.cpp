//
// Created by Ruoying Hao on 10/17/17.
//

#include "Game.hpp"

Game::Game(){
    srand(time(NULL));
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
    
    level_manager_.addLevel("Level 1", "../resource/maps/Map1.csv", "../resource/EntityLevel1.txt");
    level_manager_.addLevel("Level 2", "../resource/maps/Map2.csv", "../resource/EntityLevel2.txt");
    level_manager_.addLevel("Level 3", "../resource/maps/Map3.csv", "../resource/EntityLevel3.txt");

    //logic->load("Level 1", "../resource/maps/Map1.csv", "../resource/EntityLevel1.txt", 10 * 60);
    
    logic->load(level_manager_.getCurrentLevelName(),
                level_manager_.getCurrentTileFilename(),
                level_manager_.getCurrentEntityFilename(),
                10 * 60);
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
            if (screenManager->isOnMinigameScreen()){
                if(screenManager->isMinigameOver()){
                    if(!screenManager->isMinigameFinal()){
                        screenManager->switchToGameScreen();

                    }else{
                        screenManager->switchToWin(window);
                    }

                }

                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    screenManager->passInputToMinigame(sf::Vector2f(sf::Mouse::getPosition(*window)), window);
                    logic->update(deltaTime);
            }
            else{
                // Pass events to screen manager
                screenManager->interpretInput(events);
            }
            screenManager->render(window);
            
            if (screenManager->isOnGameScreen()){
                //std::cout << "Logic update " << std::endl;
                logic->update(deltaTime);
                switch( logic->getPlayState() ) {
                    case Logic::PlayState::MINIGAME:
                        screenManager->switchToMinigame(window);
                        break;
                    case Logic::PlayState::LOST:
                        screenManager->switchToTimeout(window);
                        break;
                    case Logic::PlayState::WON:
                        std::cout << "Game.cpp: detected game logic WON state" << std::endl;
                        // switch to intermediate / loading screen
                        // TODO; make this a win instead of a timeout
                        screenManager->switchToTransit(window);
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
                            if(screenManager->isMinigameFinal()==false){
                                screenManager->setMinigameToFinal();
                                screenManager->switchToFinalScreen(window);
                                //screenManager->switchToMiniGame();

                            }else{
                                screenManager->switchToWin(window);
                            }

                        }
                        
                        break;
                    default:
                        break;
                }
            }

            //window->display();

            clock.restart();
        }
    }
}
