#include "Screens/GameScreen.hpp"

#include "VecUtil.hpp"


const std::string GameScreen::TILESET_FILENAME = "../resource/maps/map_tiles.png";

GameScreen::GameScreen(Logic* logic) {
    logic_ = logic;
    textures_ = std::map<std::string, sf::Texture>();
    //load default keys in case custom binding fails to load
    keys_[0] = sf::Keyboard::Up;
    keys_[1] = sf::Keyboard::Down;
    keys_[2] = sf::Keyboard::Left;
    keys_[3] = sf::Keyboard::Right;
    loadKeys();
}

bool GameScreen::loadTextures() {
    textures_["tileset"] = sf::Texture();
    if (!textures_["tileset"].loadFromFile(TILESET_FILENAME)){
        return false;
    }
    /*
    for (int i = 0; i<4;i++){
        for (int j = 0; j<4;j++){
            std::cout << i*4+j << " " << j << " " << i << "\n";
            texture_coords_[i*4+j] = std::make_pair(Logic::TILE_SIZE*i, Logic::TILE_SIZE*j);
        }
    }
    */
    texture_coords_[0] = std::make_pair(Logic::TILE_SIZE*0, Logic::TILE_SIZE*0);
    texture_coords_[1] = std::make_pair(Logic::TILE_SIZE*1, Logic::TILE_SIZE*0);
    texture_coords_[2] = std::make_pair(Logic::TILE_SIZE*2, Logic::TILE_SIZE*0);
    texture_coords_[3] = std::make_pair(Logic::TILE_SIZE*3, Logic::TILE_SIZE*0);

    texture_coords_[4] = std::make_pair(Logic::TILE_SIZE*0, Logic::TILE_SIZE*1);
    texture_coords_[5] = std::make_pair(Logic::TILE_SIZE*1, Logic::TILE_SIZE*1);
    texture_coords_[6] = std::make_pair(Logic::TILE_SIZE*2, Logic::TILE_SIZE*1);
    texture_coords_[7] = std::make_pair(Logic::TILE_SIZE*3, Logic::TILE_SIZE*1);

    texture_coords_[8] = std::make_pair(Logic::TILE_SIZE*0, Logic::TILE_SIZE*2);
    texture_coords_[9] = std::make_pair(Logic::TILE_SIZE*1, Logic::TILE_SIZE*2);
    texture_coords_[10] = std::make_pair(Logic::TILE_SIZE*2, Logic::TILE_SIZE*2);
    texture_coords_[11] = std::make_pair(Logic::TILE_SIZE*3, Logic::TILE_SIZE*2);

    texture_coords_[12] = std::make_pair(Logic::TILE_SIZE*0, Logic::TILE_SIZE*3);
    texture_coords_[13] = std::make_pair(Logic::TILE_SIZE*1, Logic::TILE_SIZE*3);
    texture_coords_[14] = std::make_pair(Logic::TILE_SIZE*2, Logic::TILE_SIZE*3);
    texture_coords_[15] = std::make_pair(Logic::TILE_SIZE*3, Logic::TILE_SIZE*3);
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
    sf::Vector2f topleft = viewport_bound * (1.0f / Logic::TILE_SIZE);
    viewport_bound += window->getView().getSize(); // view bottom right
    sf::Vector2f topright = sf::Vector2f(1,1) + (viewport_bound * (1.0f / Logic::TILE_SIZE));
    
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
            v.position = sf::Vector2f(r * Logic::TILE_SIZE,
                                         c * Logic::TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first, 
                                           coord_pair.second );
            tile_vertices_.append(v);
            // top right vert
            v.position = sf::Vector2f(r * Logic::TILE_SIZE + Logic::TILE_SIZE, 
                                         c * Logic::TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first + Logic::TILE_SIZE,
                                           coord_pair.second );
            tile_vertices_.append(v);
            // bottom right vert
            v.position = sf::Vector2f(r * Logic::TILE_SIZE + Logic::TILE_SIZE, 
                                         c * Logic::TILE_SIZE + Logic::TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first + Logic::TILE_SIZE,
                                           coord_pair.second + Logic::TILE_SIZE );
            tile_vertices_.append(v);
            // bottom left vert
            v.position = sf::Vector2f(r * Logic::TILE_SIZE, 
                                         c * Logic::TILE_SIZE + Logic::TILE_SIZE);
            v.texCoords = sf::Vector2f( coord_pair.first,
                                           coord_pair.second + Logic::TILE_SIZE );
            tile_vertices_.append(v);
        }
    }
    window->draw(tile_vertices_, &textures_["tileset"]);
}

void GameScreen::renderEntities(sf::RenderWindow *window) {
	//logic_->getCharacter().render(window);
    for (auto& pair : logic_->getEntities()) {
        pair.second->render(window);
    }
    
}

void GameScreen::renderParticles(sf::RenderWindow *window) {
    // Debug line
    sf::Vector2f org;
    sf::Vector2f dir;
    if (logic_->getDebugInfo(org, dir)) {
        dir.x = dir.x * 100;
        dir.y = dir.y * 100;
        vecutil::drawDebugLine(org, org + dir, sf::Color::Red, window);
        //std::cout << "Drew debug line " << vecutil::vecInfo(org) 
         //                               << vecutil::vecInfo(dir) << std::endl;
    }
}


void GameScreen::render(sf::RenderWindow *window) {
    window->clear();
    renderTiles(window);
    renderEntities(window);
    renderParticles(window);
    centerCameraOnCharacter(window);
    window->display();
}

void GameScreen::interpretInput(std::vector<sf::Event>& events) {
    sf::Vector2f input(0,0);
    if (sf::Keyboard::isKeyPressed(keys_[1])) {
        input.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(keys_[0])) {
        input.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(keys_[2])) {
        input.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(keys_[3])) {
        input.x += 1;
    }
    logic_->registerMoveInput(input);
}

bool GameScreen::loadKeys(){
    std::cout << "GameScreen: loading keys\n";
    std::string line;
    std::ifstream myfile("../resource/keyBindings.txt");
    if ( !myfile.is_open() ) {
        std::cout << "GameScreen: Failed to open keyBindings.txt" << std::endl;
        return false;
    }
    int i = 0;
    while ( getline (myfile,line) )
    {
      //std::cout << line << '\n';
      keys_[i] = sf::Keyboard::Key(std::stoi(line));
      i += 1;
    }
    myfile.close();
    return true;
}

