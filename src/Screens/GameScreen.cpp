#include "Screens/GameScreen.hpp"

GameScreen::GameScreen(std::shared_ptr<Logic> logic) {
    logic_ = logic;
}

void GameScreen::render(sf::RenderWindow *window) {
    renderTiles(window);
    renderEntities(window);
    renderParticles(window);
}

void GameScreen::interpretInput() {

}

void GameScreen::renderTiles(sf::RenderWindow *window) {
    
}

void GameScreen::renderEntities(sf::RenderWindow *window) {
    
}

void GameScreen::renderParticles(sf::RenderWindow *window) {
    
}

