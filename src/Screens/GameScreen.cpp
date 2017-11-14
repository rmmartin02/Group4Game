#include "Screens/GameScreen.hpp"

#include "VecUtil.hpp"


const std::string GameScreen::TILESET_FILENAME = "../resource/maps/tiles.png";
const std::string GameScreen::LASER_FILENAME = "../resource/laser.png";
const std::string GameScreen::CHAR_FILENAME = "../resource/Entities/char_sprite.png";
const int GameScreen::TILE_SIZE = 32;

GameScreen::GameScreen(Logic* logic) {
    logic_ = logic;
    //textures_ = std::map<std::string, sf::Texture>();

}

bool GameScreen::loadTextures() {
   // textures_["tileset"] = sf::Texture();
    texmgr.loadTexture("tileset",TILESET_FILENAME);
    texmgr.loadTexture("laser",LASER_FILENAME);
    texmgr.loadTexture("character",CHAR_FILENAME);
    //if (!textures_["tileset"].loadFromFile(TILESET_FILENAME)){
    //    return false;
    //}
    texture_coords_[-1] = std::make_pair(0, TILE_SIZE*2);
    texture_coords_[455] = std::make_pair(TILE_SIZE*6, TILE_SIZE*4);
    texture_coords_[211] = std::make_pair(TILE_SIZE*6, TILE_SIZE*5);
    texture_coords_[210] = std::make_pair(TILE_SIZE*7, TILE_SIZE*4);
    return true;
}

void GameScreen::panCamera(sf::RenderWindow *window, sf::Vector2f amount){
    sf::View camera = window->getView();
    camera.move(amount);
    window->setView(camera);
}

void GameScreen::centerCameraOnCharacter(sf::RenderWindow *window){
	sf::View camera = window->getView();
    camera.setCenter(logic_->getCharacter().getPos());
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
    sf::Vector2f topleft = viewport_bound * (1.0f / TILE_SIZE);
    viewport_bound += window->getView().getSize(); // view bottom right
    sf::Vector2f topright = sf::Vector2f(1,1) + (viewport_bound * (1.0f / TILE_SIZE));
    
    // clamp to fit in array indices
    sf::Vector2f clamp_min = vecutil::clampVec2(topleft, sf::Vector2f(0,0), sf::Vector2f(tile_rows, tile_cols));
    sf::Vector2f clamp_max = vecutil::clampVec2(topright, sf::Vector2f(0,0), sf::Vector2f(tile_rows, tile_cols));
    
    //std::cout << "Left " << static_cast<int>(clamp_min.x) << ", Right " << static_cast<int>(clamp_max.x)
      //      << ", Top " << static_cast<int>(clamp_min.y) << ", Bottom " << static_cast<int>(clamp_max.y) << std::endl;
    
    for (int r = static_cast<int>(clamp_min.x); r < static_cast<int>(clamp_max.x); r++) {
        for (int c = static_cast<int>(clamp_min.y); c < static_cast<int>(clamp_max.y); c++) {
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
    window->draw(tile_vertices_, &texmgr.getRef("tileset"));
}

void GameScreen::renderEntities(sf::RenderWindow *window) {
	//logic_->getCharacter().render(window);
	//std::cout << "Render character " << logic_->getCharacter().getPos().x << "\n";
    for (auto& pair : logic_->getEntities()) {
        //sf::Sprite l;

        int coordinates[] = {0, 0, 32, 32};

        //if (logic_->getCharacter().getVel().x < 0) {

        //}

        pair.second->setTexture(texmgr.getRef("character"), coordinates);

        //logic_->getCharacter().isCharacter = true;

        //pair.second->setSprite(l);
        pair.second->render(window);
    }
    std::cout << "render render\n";
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
