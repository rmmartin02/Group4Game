#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"
#include "Logic.hpp"
#include <sstream>
#include <fstream>

#include "Logic.hpp"
#include "TextureManager.hpp"
#include "Screens/Screen.hpp"
#include "WalkAnimation.hpp"

class GameScreen : public Screen {

public:

    GameScreen(Logic *logic, TextureManager* tex_manager);

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

    void renderTimeLeft(sf::RenderWindow *window);

private:
    // Filename for font used to display timer
    static const std::string TIMER_FONT_FILENAME;
    
    // Name in texture manager for small blank texture
    static const std::string BLANK_TEX_NAME;
    
    // Filename for the texture file containing tile sprites
    static const std::string TILESET_FILENAME;
    // Name in texture manager for tile texture file
    static const std::string TILESET_TEX_NAME;
    // Filename for character sprite sheet
    static const std::string CHARACTER_FILENAME;
    // Name in texture manager for tile texture file
    static const std::string CHARACTER_TEX_NAME;

    // Filename for character sprite sheet
    static const std::string ENEMY1_FILENAME;
    // Name in texture manager for tile texture file
    static const std::string ENEMY1_TEX_NAME;

    // Filename for character sprite sheet
    static const std::string ENEMY2_FILENAME;
    // Name in texture manager for tile texture file
    static const std::string ENEMY2_TEX_NAME;
    
    sf::Keyboard::Key keys_[4];
    
    Logic* logic_;
    TextureManager* tex_manager_;
    
    std::map<std::string, sf::Sprite> sprites_;
    
    std::map<int, std::pair<int, int>> texture_coords_;
    
    sf::VertexArray tile_vertices_;
    
    std::unique_ptr<WalkAnimation> char_walk_;
    std::unique_ptr<WalkAnimation> enemy1_walk_;
    std::unique_ptr<WalkAnimation> enemy2_walk_;
    
    // Create sprites to be used for rendering entities
    void initializeSprites();
    
    // Get the sprite to be drawn for an entity
    sf::Sprite& getEntitySprite(Entity* entity);
    

    sf::Font text_font;
    sf::Text time_left_text;
    sf::RectangleShape time_left_background;
    float time_left_width;

    // Rendering order is tiles -> entities -> particles
    // If we find exceptions to this, we can restructure how this class orders
    // things. 
    void renderTiles(sf::RenderWindow *window);
    void renderEntities(sf::RenderWindow *window);
    void renderParticles(sf::RenderWindow *window);
    void renderEntity(sf::RenderWindow *window, Entity* entity);


};

#endif // GAMESCREEN_HPP

