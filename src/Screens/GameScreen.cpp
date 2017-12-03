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

    if (!text_font.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    time_left_text.setFont(text_font);

    time_left_text.setString("Time Left: 10:00");
    time_left_text.setFillColor(sf::Color::White);
    time_left_text.setCharacterSize(36);

    time_left_background = sf::RectangleShape (sf::Vector2f(time_left_text.getLocalBounds().width, time_left_text.getLocalBounds().height+12));
    time_left_background.setFillColor(sf::Color(66, 217, 244, 200));
    time_left_background.setOutlineThickness(5);
    time_left_background.setOutlineColor(sf::Color(128,128,128,200));
    time_left_width = time_left_text.getLocalBounds().width;
}

bool GameScreen::loadTextures() {
    textures_["tileset"] = sf::Texture();
    if (!textures_["tileset"].loadFromFile(TILESET_FILENAME)){
        return false;
    }
    for (int i = 0; i<4;i++){
        for (int j = 0; j<4;j++){
            std::cout << "GameScreen.cpp: loading tile texture coordinates: "
                      << i*4+j << " " << j << " " << i << "\n";
            texture_coords_[i*4+j] = std::make_pair(Logic::TILE_SIZE*j, Logic::TILE_SIZE*i);
        }
    }
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
            
            auto coord_pair = texture_coords_[tiles[c][r]];
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

void GameScreen::renderTimeLeft(sf::RenderWindow *window){
    int time = static_cast<int>(logic_->getTimeLeft());
    int minutes = time/60;
    int seconds = time%60;
    time_left_text.setString("Time Left: " + std::to_string(minutes) + ":" + (seconds>=10 ? std::to_string(seconds) : "0" + std::to_string(seconds)));
    time_left_text.setPosition(sf::Vector2f(window->getView().getCenter().x - time_left_width/2, 
        window->getView().getCenter().y-window->getView().getSize().y/2+10));
    window->draw(time_left_background, time_left_text.getTransform());
    window->draw(time_left_text);
}


void GameScreen::render(sf::RenderWindow *window) {
    window->clear();
    renderTiles(window);
    renderEntities(window);
    renderParticles(window);
    centerCameraOnCharacter(window);
    renderTimeLeft(window);
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

    // for sight obstruction testing, check mouse position
    for (auto event : events) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            sf::Vector2f charPos = logic_->getCharacter().getPos();
            mousePos = mousePos + sf::Vector2f(-400, -300) + charPos;
            std::cout << "GameScreen.cpp: mouse pos " << vecutil::vecInfo(mousePos) << std::endl; 
            std::cout << "GameScreen.cpp: char pos  " << vecutil::vecInfo(logic_->getCharacter().getPos()) << std::endl;
            
            sf::Vector2f wall_hit;
            // Check if there is an obstruction between where is clicked and the center of the character.
            if (logic_->sightObstructed(logic_->getCharacter().getPos(),
                                        mousePos,
                                        wall_hit)) {
                std::cout << "GameScreen.cpp: sight blocked at " << vecutil::vecInfo(wall_hit) << std::endl;
            }
            else {
                std::cout << "GameScreen.cpp: sight unobstructed" << std::endl;
            }
        }
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

