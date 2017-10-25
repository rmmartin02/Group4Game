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
    texture_coords_[-1] = std::make_pair(0, TILE_SIZE*2);
    texture_coords_[455] = std::make_pair(TILE_SIZE*6, TILE_SIZE*4);
    texture_coords_[211] = std::make_pair(TILE_SIZE*6, TILE_SIZE*5);
    texture_coords_[210] = std::make_pair(TILE_SIZE*7, TILE_SIZE*4);
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
    int tile_rows = tiles.size();
    int tile_cols = tiles[0].size();
    
    tile_vertices_.clear();
    tile_vertices_.setPrimitiveType(sf::Quads);
    //tile_vertices_.resize(tiles.size() * tiles[0].size() * 4);
    
    sf::Vector2f viewport_bound = window->getView().getCenter()  - 
                                (window->getView().getSize()/2.f); // view top left
    // determine viewport bounds so we can cull and not draw tiles that aren't visible
    int left = static_cast<int>(viewport_bound.x/TILE_SIZE);
    int top = static_cast<int>(viewport_bound.y/TILE_SIZE);
    viewport_bound += window->getView().getSize(); // view bottom right
    int right = 1 + static_cast<int>(viewport_bound.x/TILE_SIZE);
    int bottom = 1 + static_cast<int>(viewport_bound.y/TILE_SIZE);
    // clamp to fit in array indices
    left=std::max(0,std::min(left,tile_rows));
    top=std::max(0,std::min(top,tile_cols));
    right=std::max(0,std::min(right,tile_rows));
    bottom=std::max(0,std::min(bottom,tile_cols));
    
    //std::cout << "Left " << left << ", Right " << right << ", Top " << top << ", Bottom " << bottom << std::endl;
    
    for (int r = left; r < right; r++) {
        for (int c = top; c < bottom; c++) {
            
            //std::cout << "Tile at " << r << ", " << c << " is " << tiles[r][c] << std::endl;
            
            auto coord_pair = texture_coords_[tiles[r][c]];
            
            //std::cout << "coord " << coord_pair.first << "," << coord_pair.second << ".\n";
            
            // top left vert
            sf::Vertex v;
            v.position = sf::Vector2f(r * TILE_SIZE,
                                         c * TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first, 
                                           coord_pair.second );
            tile_vertices_.append(v);
            // top right vert
            v.position = sf::Vector2f(r * TILE_SIZE + TILE_SIZE, 
                                         c * TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first + TILE_SIZE,
                                           coord_pair.second );
            tile_vertices_.append(v);
            // bottom right vert
            v.position = sf::Vector2f(r * TILE_SIZE + TILE_SIZE, 
                                         c * TILE_SIZE + TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first + TILE_SIZE,
                                           coord_pair.second + TILE_SIZE );
            tile_vertices_.append(v);
            // bottom left vert
            v.position = sf::Vector2f(r * TILE_SIZE, 
                                         c * TILE_SIZE + TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first,
                                           coord_pair.second + TILE_SIZE );
            tile_vertices_.append(v);
        }
    }
    window->draw(tile_vertices_, &textures_["tileset"]);
}

void GameScreen::renderEntities(sf::RenderWindow *window) {
	//logic_->getCharacter().render(window);
	//std::cout << "Render character " << logic_->getCharacter().getPos().x << "\n";
    for (auto pair : logic_->getEntities()) {
        pair.second.render(window);
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
    //sf::sleep(sf::milliseconds(200));
}

void GameScreen::interpretInput() {

}
