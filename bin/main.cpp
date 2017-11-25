#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main(int argc, char** argv)
{

  // create main window
    Game game;
    game.initialize();
    game.Loop();

    return 0;

  // Done.
  return 0;
}
