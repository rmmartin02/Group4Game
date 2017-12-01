#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"
#include "Logic.hpp"
#include <sstream>
#include <fstream>

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
    
    sf::Keyboard::Key keys_[4];
    
    Logic* logic_;
    
    std::map<std::string, sf::Texture> textures_;
    std::map<int, std::pair<int, int>> texture_coords_;
    
    sf::VertexArray tile_vertices_;

    sf::Font text_font;
    sf::Text time_left_text;
    sf::RectangleShape time_left_background;

    // Rendering order is tiles -> entities -> particles
    // If we find exceptions to this, we can restructure how this class orders
    // things. 
    void renderTiles(sf::RenderWindow *window);
    void renderEntities(sf::RenderWindow *window);
    void renderParticles(sf::RenderWindow *window);
    void renderTimeLeft(sf::RenderWindow *window);

};

#endif // GAMESCREEN_HPP

