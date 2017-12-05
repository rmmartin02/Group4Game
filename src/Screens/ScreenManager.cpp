#include "Screens/ScreenManager.hpp"
#include "Logic.hpp"

ScreenManager::ScreenManager(Logic *logic){
	logic_ = logic;
	game_screen = new GameScreen(logic);
	menu_screen = new MenuScreen();
	controls_screen = new ControlsScreen();
    timeout_screen = new TimeoutScreen();
    minigame_screen = new MiniGameScreen();
    info_screen = new InfoScreen();
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
   // view.setCenter(sf::Vector2f(400,300));
    sf::View camera = window->getView();
    camera.setCenter(sf::Vector2f(400,300));
    window->setView(camera);
    current_screen=timeout_screen;
}

bool ScreenManager::isOnMinigameScreen(){
    return current_screen==minigame_screen;
}