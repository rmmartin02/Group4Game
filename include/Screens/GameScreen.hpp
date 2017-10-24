#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screens/Screen.hpp"
#include "Logic.hpp"

class GameScreen : public Screen {

public:
    GameScreen(Logic logic);
    void render(sf::RenderWindow *window);
    void interpretInput();

private:
    Logic logic_;

    // Rendering order is tiles -> entities -> particles
    // If we find exceptions to this, we can restructure how this class orders
    // things. 
    void renderTiles(sf::RenderWindow *window);
    void renderEntities(sf::RenderWindow *window);
    void renderParticles(sf::RenderWindow *window);

};

#endif // GAMESCREEN_HPP

