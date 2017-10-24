#include "Screens/GameScreen.hpp"


const std::string GameScreen::TILESET_FILENAME = "../resource/maps/tiles.png";
const int GameScreen::TILE_SIZE = 32;

GameScreen::GameScreen(Logic* logic) {

    logic_ = logic;
    textures_ = std::map<std::string, sf::Texture>();
}

bool GameScreen::loadTextures() {
    textures_["tileset"] = sf::Texture();
    if (!textures_["tileset"].loadFromFile(TILESET_FILENAME)){
        return false;
    }
    texture_coords_[-1] = std::make_pair(0, 0);
    texture_coords_[1] = std::make_pair(0, TILE_SIZE*2);
    texture_coords_[2] = std::make_pair(TILE_SIZE*6, TILE_SIZE*4);
    return true;
}

void GameScreen::panCamera(sf::RenderWindow *window, sf::Vector2f amount){
    sf::View camera = window->getView();
    camera.move(amount);
    //std::cout << "cam pan " << amount.x << "," << amount.y << std::endl;
    window->setView(camera);
}

void GameScreen::renderTiles(sf::RenderWindow *window) {
    auto tiles = logic_->getTiles();
    tile_vertices_ = sf::VertexArray(sf::Quads);
    for (int r = 0; r != tiles.size(); r++) {
        for (int c = 0; c != tiles[r].size(); c++) {
            
            //std::cout << "Tile at " << r << ", " << c << " is " << tiles[r][c] << std::endl;
            
            auto coord_pair = texture_coords_[tiles[r][c]];
            //std::cout << "coord " << coord_pair.first << "," << coord_pair.second << ".\n";
            
            // top left vert
            sf::Vertex v1;
            v1.position = sf::Vector2f(r * TILE_SIZE,
                                         c * TILE_SIZE);
            v1.texCoords = sf::Vector2f( coord_pair.first, 
                                           coord_pair.second );
            tile_vertices_.append(v1);
            // top right vert
            sf::Vertex v2;
            v2.position = sf::Vector2f(r * TILE_SIZE + TILE_SIZE, 
                                         c * TILE_SIZE);
            v2.texCoords = sf::Vector2f( coord_pair.first + TILE_SIZE,
                                           coord_pair.second );
            tile_vertices_.append(v2);
            // bottom right vert
            sf::Vertex v3;
            v3.position = sf::Vector2f(r * TILE_SIZE + TILE_SIZE, 
                                         c * TILE_SIZE + TILE_SIZE);
            v3.texCoords = sf::Vector2f( coord_pair.first + TILE_SIZE,
                                           coord_pair.second + TILE_SIZE );
            tile_vertices_.append(v3);
            // bottom left vert
            sf::Vertex v4;
            v4.position = sf::Vector2f(r * TILE_SIZE, 
                                         c * TILE_SIZE + TILE_SIZE);
            v4.texCoords = sf::Vector2f( coord_pair.first,
                                           coord_pair.second + TILE_SIZE );
            tile_vertices_.append(v4);
            window->draw(tile_vertices_, &textures_["tileset"]);
        }
    }
}

void GameScreen::renderEntities(sf::RenderWindow *window) {

	//logic_->getCharacter().render(window);
	//std::cout << "Render character " << logic_->getCharacter().getPos().x << "\n";
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
    sf::sleep(sf::milliseconds(200));
}

void GameScreen::interpretInput() {

}
