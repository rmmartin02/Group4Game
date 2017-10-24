#include "Screens/GameScreen.hpp"
#include "Logic.hpp"

GameScreen::GameScreen(Logic *logic) {
    logic_ = logic;
}

void GameScreen::renderTiles(sf::RenderWindow *window) {
    
}

void GameScreen::renderEntities(sf::RenderWindow *window) {
	logic_.getCharacter().render(window);
	std::cout << "Render character " << logic_.getCharacter().getPos().x << "\n";
}

void GameScreen::renderParticles(sf::RenderWindow *window) {
    
}


void GameScreen::render(sf::RenderWindow *window) {
	window->clear();
    renderTiles(window);
    renderEntities(window);
    renderParticles(window);
    window->display();
}

void GameScreen::interpretInput() {

}
