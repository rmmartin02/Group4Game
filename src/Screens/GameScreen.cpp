#include "Screens/GameScreen.hpp"
#include "Logic.hpp"

const std::string GameScreen::TILESET_FILENAME = "../resource/maps/tiles.png";

GameScreen::GameScreen(Logic* logic) {
    logic_ = logic;
    textures_ = std::map<std::string, sf::Texture>();
}

bool GameScreen::loadTextures() {
    textures_["tileset"] = sf::Texture();
    if (!textures_["tileset"].loadFromFile(TILESET_FILENAME)){
        return false;
    }
    texture_coords_[-1] = std::make_pair(64, 64);
    texture_coords_[1] = std::make_pair(0, 32);
    return true;
}

void GameScreen::renderTiles(sf::RenderWindow *window) {
    auto tiles = logic_->getTiles();
    for (int r = 0; r != tiles.size(); r++) {
        for (int c = 0; c != tiles[r].size(); c++) {
            std::cout << "Tile at " << r << ", " << c << " is " << tiles[r][c] << std::endl;
        }
    }
}

void GameScreen::renderEntities(sf::RenderWindow *window) {
	for (auto const& x : logic_->getEntities()) {
        x.second.render(window);   
    }
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
