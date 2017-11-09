#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screens/Screen.hpp"
#include "Logic.hpp"
#include <sstream>
#include <fstream>

class GameScreen : public Screen {

public:

    GameScreen(Logic *logic);

    void render(sf::RenderWindow *window);
    void interpretInput(sf::Event event);
    
    // Return true if successfully loaded, false otherwise
    bool loadTextures();
    
    // Move the view
    void panCamera(sf::RenderWindow*, sf::Vector2f);

    //Center view on Character
    void centerCameraOnCharacter(sf::RenderWindow*);

    //loads current key bindings
    bool loadKeys();

    //rebinds direction to given key
    void rebindKey(Logic::Direction direction, sf::Keyboard::Key key);

private:

    // Filename for the texture file containing tile sprites
    static const std::string TILESET_FILENAME;
    
    // Represents the size of a tile, in pixels on the tileset file,
    // and in SFML's drawing units. We may want to separate the two
    // in the future.
    static const int TILE_SIZE;

    sf::Keyboard::Key up_key = sf::Keyboard::Up;
    sf::Keyboard::Key down_key = sf::Keyboard::Down;
    sf::Keyboard::Key left_key = sf::Keyboard::Left;
    sf::Keyboard::Key right_key = sf::Keyboard::Right;
    
    Logic* logic_;
    
    std::map<std::string, sf::Texture> textures_;
    std::map<int, std::pair<int, int>> texture_coords_;
    
    sf::VertexArray tile_vertices_;
    

    // Rendering order is tiles -> entities -> particles
    // If we find exceptions to this, we can restructure how this class orders
    // things. 
    void renderTiles(sf::RenderWindow *window);
    void renderEntities(sf::RenderWindow *window);
    void renderParticles(sf::RenderWindow *window);

};

#endif // GAMESCREEN_HPP

