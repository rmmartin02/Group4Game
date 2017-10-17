#include <SFML/Graphics.hpp>
#include "DEFINITION.hpp"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Agent P: Infiltration");
  // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    // background
    sf::Texture background;
    if (!background.loadFromFile("../resource/background/resized_bg.png"))
    {
      // error...
    }

    sf::Sprite bg(background);

    App.draw(bg);


    // logo
    sf::Texture logo;

    if (!background.loadFromFile("../resource/API.png"))
    {
      // error...
    }

    sf::Sprite logo_sprite(logo);

    App.draw(logo_sprite);


    // Title
    sf::Font titleFont;

    if (!titleFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
      // error...
    }

    sf::Text title;
    title.setFont(titleFont);

    title.setString("Agent P: Infiltration");
    title.setColor(sf::Color::White);
    title.setCharacterSize(75);
    title.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - title.getLocalBounds().width/2, SCREEN_HEIGHT/4));

    App.draw(title);

    // Tagline

      sf::Font taglineFont;

      if (!taglineFont.loadFromFile("../resource/fonts/Adventure.otf"))
      {
          // error...
      }

      sf::Text tagline;
      title.setFont(taglineFont);

      title.setString("You have 10 minutes. Save the Earth.");
      title.setColor(sf::Color::White);
      title.setCharacterSize(36);
      title.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - title.getLocalBounds().width/2, SCREEN_HEIGHT/2.5));

      App.draw(title);

      sf::RectangleShape start;
      start.setSize(sf::Vector2f(200, 50));
      start.setOutlineColor(sf::Color::White);
      start.setFillColor(sf::Color::Transparent);
      start.setOutlineThickness(5);
      start.setPosition(SCREEN_WIDTH/2 - start.getLocalBounds().width/2, SCREEN_HEIGHT/2);

      App.draw(start);



      // display
    App.display();
  }

  // Done.
  return 0;
}
