#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include <sstream>
#include <fstream>

#include "Logic.hpp"
#include "TextureManager.hpp"
#include "Screens/Screen.hpp"

class GameScreen : public Screen {

public:

    GameScreen(Logic *logic);

    void render(sf::RenderWindow *window);
    void interpretInput(std::vector<sf::Event>& events);
    
    // Return true if successfully loaded, false otherwise
    bool loadTextures();
    
    // Move the view
    void panCamera(sf::RenderWindow*, sf::Vector2f);

    //Center view on Character
    void centerCameraOnCharacter(sf::RenderWindow*);

    //loads current key bindings
    bool loadKeys();

private:

    // Filename for the texture file containing tile sprites
    static const std::string TILESET_FILENAME;

    static const std::string TILESET_TEX_NAME;
    
    sf::Keyboard::Key keys_[4];
    
    Logic* logic_;
    
    TextureManager tex_manager_;
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

