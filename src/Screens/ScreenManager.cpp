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

void ScreenManager::interpretInput(sf::Event Event){
	//check for events that might change the screen
	if(currentScreen == menuScreen){
		if (Event.type == sf::Event::KeyPressed){
        	if (Event.key.code == sf::Keyboard::S){
            	currentScreen = gameScreen;
            }
    	}
	}
	//otherwise send event to appropriate screen to interpret
	currentScreen->interpretInput(Event);
}

bool ScreenManager::loadTextures(){
	gameScreen->loadTextures();
}

bool ScreenManager::isOnGameScreen(){
	return currentScreen==gameScreen;
}