#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screens/Screen.hpp"
#include "Logic.hpp"

class GameScreen : public Screen {

public:

    GameScreen(Logic *logic);

    void render(sf::RenderWindow *window);
    void interpretInput();
    
    // Return true if successfully loaded, false otherwise
    bool loadTextures();
    
    // Move the view
    void panCamera(sf::RenderWindow*, sf::Vector2f);

private:

    // Filename for the texture file containing tile sprites
    static const std::string TILESET_FILENAME;
    
    // Represents the size of a tile, in pixels on the tileset file,
    // and in SFML's drawing units. We may want to separate the two
    // in the future.
    static const int TILE_SIZE;
    
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

