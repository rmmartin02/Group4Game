#include "Screens/ScreenManager.hpp"
#include "Logic.hpp"

ScreenManager::ScreenManager(Logic *logic){
	logic_ = logic;
	game_screen = new GameScreen(logic, &tex_manager_);
	menu_screen = new MenuScreen();
	controls_screen = new ControlsScreen();
    timeout_screen = new TimeoutScreen();
    minigame_screen = new MiniGameScreen();
	minigame_screen->setShuffleLength(40);
    info_screen = new InfoScreen();
    transit_screen = new TransitScreen();
    win_screen = new WinScreen();
    final_screen = new FinalScreen();
	current_screen = menu_screen;
}

void ScreenManager::render(sf::RenderWindow *window){
	current_screen->render(window);
}

void ScreenManager::interpretInput(std::vector<sf::Event>& events){
    std::vector<sf::Event> screen_events;
    for (auto event : events) {
        //check for events that might change the screen
        bool eventAccepted = false;
        if(current_screen == menu_screen){
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Return){
                    std::cout << "ScreenManager: menu screen has highlighted "
                              << menu_screen->getHighlighted() << std::endl;
                    if(menu_screen->getHighlighted()==0){
                        current_screen = game_screen;
                    }
                    else if(menu_screen->getHighlighted()==1){
                        current_screen = controls_screen;
                    }else{
                        current_screen = info_screen;
                    }
                    eventAccepted = true;
                }
                if(event.key.code==sf::Keyboard::M){
                    current_screen = minigame_screen;

                }
            }
        }
        else if(current_screen == controls_screen){
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Return){
                    if(controls_screen->getHighlighted()==4){
                        controls_screen->saveKeys();
                        current_screen = menu_screen;
                        game_screen->loadKeys();
                        controls_screen->resetHighlighted();
                        eventAccepted = true;
                    }
                }
            }
        }
        else if(current_screen==info_screen){
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Return){
                    current_screen=menu_screen;

                }
                eventAccepted = true;

            }

        }
        else if (current_screen == timeout_screen) {
//            if (event.type == sf::Event::KeyPressed) {
//                if (event.key.code == sf::Keyboard::Space) {
//                    //std::cout << "ScreenManager: debug: tried to switch back to gamescreen" << std::endl;
//                    current_screen = game_screen;
//                }
//                eventAccepted = true;
//            }
        }
        else if(current_screen == transit_screen){
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    std::cout << "ScreenManager: debug: tried to switch back to gamescreen" << std::endl;
                    current_screen = game_screen;
                }
                eventAccepted = true;
            }

        }else if(current_screen==final_screen){
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    std::cout << "ScreenManager: debug: tried to switch to minigame screen" << std::endl;
                    current_screen = minigame_screen;
                }
                eventAccepted = true;
            }
        }
        //otherwise send event to appropriate screen to interpret
        if(!eventAccepted)
            screen_events.push_back(event);
    }
    current_screen->interpretInput(screen_events);
}

bool ScreenManager::loadTextures(){
	game_screen->loadTextures();
}

bool ScreenManager::isOnGameScreen(){
	return current_screen==game_screen;
}

void ScreenManager::switchToTimeout(sf::RenderWindow* window){
    sf::View camera = window->getView();

    camera.setCenter(sf::Vector2f(400,300));
    window->setView(camera);
    current_screen=timeout_screen;

}

void ScreenManager::switchToGameScreen(){
    minigame_screen->gameWon = false;
    minigame_screen->spriteBoardCreated = false;
    minigame_screen->shuffled = false;
    logic_->setPlayState(Logic::PLAYING);
    current_screen=game_screen;
}

void ScreenManager::switchToFinalScreen(sf::RenderWindow* window){
    minigame_screen->gameWon = false;
    minigame_screen->spriteBoardCreated = false;
    minigame_screen->shuffled = false;
    sf::View camera = window->getView();
    camera.setCenter(sf::Vector2f(400,300));
    window->setView(camera);
    current_screen=final_screen;


}

void ScreenManager::switchToWin(sf::RenderWindow* window){
    //minigame_screen->gameWon = false;
    //minigame_screen->spriteBoardCreated = false;
    //minigame_screen->shuffled = false;
    sf::View camera = window->getView();
    camera.setCenter(sf::Vector2f(400,300));
    window->setView(camera);
    //logic_->setPlayState(Logic::WIN);
    current_screen=win_screen;
}

void ScreenManager::switchToTransit(sf::RenderWindow* window){
    //minigame_screen->gameWon = false;
    //minigame_screen->spriteBoardCreated = false;
    //minigame_screen->shuffled = false;
    sf::View camera = window->getView();
    camera.setCenter(sf::Vector2f(400,300));
    window->setView(camera);
    //logic_->setPlayState(Logic::WIN);
    current_screen=transit_screen;
}


void ScreenManager::switchToMinigame(sf::RenderWindow* window){
    sf::View camera = window->getView();
    camera.setCenter(sf::Vector2f(400,300));
    window->setView(camera);
    current_screen=minigame_screen;
}

bool ScreenManager::isOnMinigameScreen(){
    return current_screen==minigame_screen;
}

bool ScreenManager::isMinigameOver(){
    return minigame_screen->gameWon;
}

void ScreenManager::passInputToMinigame(sf::Vector2<float> coordinates, sf::RenderWindow* window){
    minigame_screen->moveOnClick(minigame_screen->shuffledPuzzle, coordinates, window);
}

bool ScreenManager::isMinigameFinal(){
    return minigame_screen->getMinigameFinal();
}

void ScreenManager::setMinigameToFinal(){
    minigame_screen->setMinigameFinal();
}