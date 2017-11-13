#include "Screens/ScreenManager.hpp"
#include "Logic.hpp"

ScreenManager::ScreenManager(Logic *logic){
	logic_ = logic;
	gameScreen = new GameScreen(logic);
	menuScreen = new MenuScreen();
	controlsScreen = new ControlsScreen();
	currentScreen = controlsScreen;
}

void ScreenManager::render(sf::RenderWindow *window){
	currentScreen->render(window);
}

void ScreenManager::interpretInput(sf::Event event){
	//check for events that might change the screen
	if(currentScreen == menuScreen){
		if (event.type == sf::Event::KeyPressed){
        	if (event.key.code == sf::Keyboard::S){
            	currentScreen = gameScreen;
            }
            if (event.key.code == sf::Keyboard::M){
            	currentScreen = controlsScreen;
            }
    	}
	}
	else if(currentScreen == controlsScreen){
		if (event.type == sf::Event::KeyPressed){
        	if (event.key.code == sf::Keyboard::B){
        		controlsScreen->saveKeys();
            	currentScreen = menuScreen;
            	gameScreen->loadKeys();
            }
        }
	}
	//otherwise send event to appropriate screen to interpret
	currentScreen->interpretInput(event);
}

bool ScreenManager::loadTextures(){
	gameScreen->loadTextures();
}

bool ScreenManager::isOnGameScreen(){
	return currentScreen==gameScreen;
}