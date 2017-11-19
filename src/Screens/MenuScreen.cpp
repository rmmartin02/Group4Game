#include "Screens/MenuScreen.hpp"

MenuScreen::MenuScreen(){
    //background
    if (!background.loadFromFile("../resource/background/start_background.jpg"))
    {
        // error...
    }
    bg.setTexture(background);

    //logo

    if (!logo.loadFromFile("../resource/API.png"))
    {
        // error...
    }
    logo_sprite.setTexture(logo);
    logo_sprite.setScale(LOGO_SCALE,LOGO_SCALE);
    logo_sprite.setPosition(SCREEN_WIDTH/2 - 476*LOGO_SCALE,100);


    //tagline

    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    tagline.setFont(textFont);

    tagline.setString("You Have 10 Minutes, Save the Earth.");
    tagline.setFillColor(sf::Color::White);
    tagline.setCharacterSize(36);
    tagline.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - tagline.getLocalBounds().width/2, logo_sprite.getLocalBounds().height+logo_sprite.getPosition().y-50));



    //start
    start.setFont(textFont);

    start.setString("Start");
    start.setFillColor(sf::Color::White);
    start.setCharacterSize(40);
    start.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - start.getLocalBounds().width/2, SCREEN_HEIGHT/2+20));
    /*
    start.setSize(sf::Vector2f(200, 50));
    start.setOutlineColor(sf::Color::White);
    start.setFillColor(sf::Color::Transparent);
    start.setOutlineThickness(5);
    start.setPosition(SCREEN_WIDTH/2 - start.getLocalBounds().width/2, SCREEN_HEIGHT/2);
     */

    options.setFont(textFont);

    options.setString("Options");
    options.setFillColor(sf::Color::White);
    options.setCharacterSize(40);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - options.getLocalBounds().width/2, start.getLocalBounds().height+start.getPosition().y+20));

    menu_options[0] = &start;
    menu_options[1] = &options;
    menu_options[highlighted]->setFillColor(sf::Color::Green);
}

void MenuScreen::render(sf::RenderWindow *window){
    //std::cout <<"render Menu Screen\n";
    window->clear();
    window->draw(bg);
    window->draw(logo_sprite);
    window->draw(tagline);
    window->draw(start);
    window->draw(options);
    window->display();

}

void MenuScreen::interpretInput(std::vector<sf::Event>& events) {
    for ( auto event : events ) {
        if (event.type == sf::Event::KeyPressed){
            std::cout<<highlighted<<"\n";
            if (event.key.code == sf::Keyboard::Up){
                menu_options[highlighted]->setFillColor(sf::Color::White);
                //because c++ has a remainder operator NOT a modulus operator
                if(highlighted==0)
                    highlighted = 1;
                else
                    highlighted = (highlighted-1)%2;
                menu_options[highlighted]->setFillColor(sf::Color::Green);
            }
            if (event.key.code == sf::Keyboard::Down){
                menu_options[highlighted]->setFillColor(sf::Color::White);
                highlighted = (highlighted+1)%2;
                menu_options[highlighted]->setFillColor(sf::Color::Green);
            }
            std::cout<<highlighted<<"\n";
        }
    }
}

int MenuScreen::getHighlighted(){
    return highlighted;
}
