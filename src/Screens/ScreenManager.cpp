#include "Screens/ScreenManager.hpp"
#include "Logic.hpp"

ScreenManager::ScreenManager(Logic *logic){
	logic_ = logic;
	game_screen = new GameScreen(logic);
	menu_screen = new MenuScreen();
	controls_screen = new ControlsScreen();
    timeout_screen = new TimeoutScreen();
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
                        current_screen = timeout_screen;
                    }
                    else{
                        current_screen = controls_screen;
                    }
                    eventAccepted = true;
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

