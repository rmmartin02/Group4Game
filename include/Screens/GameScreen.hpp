#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Logic.hpp"

class GameScreen : Screen {

public:
    GameScreen(Logic& logic);
    void render(sf::RenderWindow *window) override;
    void interpretInput() override;

private:
    std::shared_ptr<Logic> logic_;

    // Rendering order is tiles -> entities -> particles
    // If we find exceptions to this, we can restructure how this class orders
    // things. 
    void renderTiles();
    void renderEntities();
    void renderParticles();

};

#endif // GAMESCREEN_HPP

