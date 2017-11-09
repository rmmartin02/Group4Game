#include "Screens/GameScreen.hpp"

#include "VecUtil.hpp"


const std::string GameScreen::TILESET_FILENAME = "../resource/maps/tiles.png";
const int GameScreen::TILE_SIZE = 32;

GameScreen::GameScreen(Logic* logic) {
    logic_ = logic;
    textures_ = std::map<std::string, sf::Texture>();
    loadKeys();
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
	//std::cout <<"render Game Screen\n";
    window->clear();
    renderTiles(window);
    renderEntities(window);
    renderParticles(window);
    centerCameraOnCharacter(window);
    window->display();
}

void GameScreen::interpretInput(sf::Event Event) {
    sf::Vector2f cam_offset(0,0);
    bool key_pressed = false;
    if (sf::Keyboard::isKeyPressed(down_key)){
        logic_->registerMoveInput(Logic::Direction::DOWN);
        key_pressed = true;
        //cam_offset.y -= CAMERA_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(up_key)){
        logic_->registerMoveInput(Logic::Direction::UP);
        key_pressed = true;
        //cam_offset.y += CAMERA_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(left_key)){
        logic_->registerMoveInput(Logic::Direction::LEFT);
        key_pressed = true;
        //cam_offset.x += CAMERA_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(right_key)){
        logic_->registerMoveInput(Logic::Direction::RIGHT);
        key_pressed = true;
        //cam_offset.x -= CAMERA_SPEED * deltaTime;
    }
    if ( !key_pressed ) {
        logic_->registerMoveInput(Logic::Direction::NONE);
    }
}

void GameScreen::rebindKey(Logic::Direction direction, sf::Keyboard::Key key){
    switch (direction){
        case Logic::Direction::UP:
            up_key = key;
            break;
        case Logic::Direction::DOWN:
            down_key = key;
            break;
        case Logic::Direction::LEFT:
            left_key = key;
            break;
        case Logic::Direction::RIGHT:
            right_key = key;
            break;
    }
}

bool GameScreen::loadKeys(){
    std::cout << "load keys\n";
    std::string line;
    std::ifstream myfile("../resource/keyBindings.txt");
    if ( !myfile.is_open() ) {
        std::cout << "Failed to open keyBindings.txt" << std::endl;
        return false;
    }
    while ( getline (myfile,line) )
    {
      std::cout << line << '\n';
    }
    myfile.close();
    return true;
}