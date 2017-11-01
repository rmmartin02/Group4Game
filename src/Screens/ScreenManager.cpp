#include "Screens/ScreenManager.hpp"

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
	if(currentScreen = menuScreen){
		if (Event.type == sf::Event::KeyPressed){
        	if (Event.key.code == sf::Keyboard::S){
            	window->close();
            }
    	}
	}
}

bool ScreenManager::loadTextures(){
	gameScreen->loadTextures();
}