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
	if(currentScreen == menuScreen){
		if (Event.type == sf::Event::KeyPressed){
        	if (Event.key.code == sf::Keyboard::S){
            	currentScreen = gameScreen;
            }
    	}
	}
	if(currentScreen == gameScreen){
		sf::Vector2f cam_offset(0,0);
		bool key_pressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			logic_->registerMoveInput(Logic::Direction::DOWN);
			key_pressed = true;
			//cam_offset.y -= CAMERA_SPEED * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			logic_->registerMoveInput(Logic::Direction::UP);
			key_pressed = true;
			//cam_offset.y += CAMERA_SPEED * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			logic_->registerMoveInput(Logic::Direction::LEFT);
			key_pressed = true;
			//cam_offset.x += CAMERA_SPEED * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			logic_->registerMoveInput(Logic::Direction::RIGHT);
			key_pressed = true;
			//cam_offset.x -= CAMERA_SPEED * deltaTime;
		}
		if ( !key_pressed ) {
			logic_->registerMoveInput(Logic::Direction::NONE);
		}
	}
}

bool ScreenManager::loadTextures(){
	gameScreen->loadTextures();
}

bool ScreenManager::isOnGameScreen(){
	return currentScreen==gameScreen;
}