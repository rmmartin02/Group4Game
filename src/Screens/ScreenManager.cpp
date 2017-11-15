#include "Screens/ScreenManager.hpp"
#include "Logic.hpp"

ScreenManager::ScreenManager(Logic *logic){
	logic_ = logic;
	gameScreen = new GameScreen(logic);
	menuScreen = new MenuScreen();
	currentScreen = menuScreen;
}

void ScreenManager::render(sf::RenderWindow *window){
	currentScreen->render(window);
}

void ScreenManager::interpretInput(std::vector<sf::Event>& events){
    //check for events that might change the screen
    if (currentScreen == menuScreen){
        for (auto it = events.begin(); it != events.end(); ++it) {
            auto event = *it;
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::S){
                    currentScreen = gameScreen;
                }
            }
        }
    }
    //otherwise send event to appropriate screen to interpret
    currentScreen->interpretInput(events);
}

bool ScreenManager::loadTextures(){
	gameScreen->loadTextures();
}

bool ScreenManager::isOnGameScreen(){
	return currentScreen==gameScreen;
}
