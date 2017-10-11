#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Agent P: Infiltration");

  int screen_width = 800;
  int screen_height = 600;

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
    if (!background.loadFromFile("/Users/arman/CLionProjects/Group4Game/resource/background/resized_bg.png"))
    {
      // error...
    }

    sf::Sprite bg(background);

    App.draw(bg);


    // logo
    sf::Texture logo;

    if (!background.loadFromFile("/Users/arman/CLionProjects/Group4Game/resource/API.png"))
    {
      // error...
    }

    sf::Sprite logo_sprite(logo);

    App.draw(logo_sprite);


    // Title
    sf::Font titleFont;

    if (!titleFont.loadFromFile("/Users/arman/CLionProjects/Group4Game/resource/fonts/Adventure.otf"))
    {
      // error...
    }

    sf::Text title;
    title.setFont(titleFont);

    title.setString("Agent P: Infiltration");
    title.setColor(sf::Color::White);
    title.setCharacterSize(75);
    title.setPosition(sf::Vector2f(screen_width/2 - title.getLocalBounds().width/2, screen_height/4));

    App.draw(title);

    // Tagline

      sf::Font taglineFont;

      if (!taglineFont.loadFromFile("/Users/arman/CLionProjects/Group4Game/resource/fonts/Adventure.otf"))
      {
          // error...
      }

      sf::Text tagline;
      title.setFont(taglineFont);

      title.setString("You have 10 minutes. Save the Earth.");
      title.setColor(sf::Color::White);
      title.setCharacterSize(36);
      title.setPosition(sf::Vector2f(screen_width/2 - title.getLocalBounds().width/2, screen_height/2.5));

      App.draw(title);

      sf::RectangleShape start;
      start.setSize(sf::Vector2f(200, 50));
      start.setOutlineColor(sf::Color::White);
      start.setFillColor(sf::Color::Transparent);
      start.setOutlineThickness(5);
      start.setPosition(screen_width/2 - start.getLocalBounds().width/2, screen_height/2);

      App.draw(start);



      // display
    App.display();
  }

  // Done.
  return 0;
}
