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
    tagline.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - tagline.getLocalBounds().width/2, SCREEN_HEIGHT/2.5));



    //start
    start.setFont(textFont);

    start.setString("Start [s]");
    start.setFillColor(sf::Color::White);
    start.setCharacterSize(30);
    start.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - start.getLocalBounds().width/2, SCREEN_HEIGHT/2));
    /*
    start.setSize(sf::Vector2f(200, 50));
    start.setOutlineColor(sf::Color::White);
    start.setFillColor(sf::Color::Transparent);
    start.setOutlineThickness(5);
    start.setPosition(SCREEN_WIDTH/2 - start.getLocalBounds().width/2, SCREEN_HEIGHT/2);
     */

}

void MenuScreen::render(sf::RenderWindow *window){

    window->clear();
    window->draw(bg);
    window->draw(logo_sprite);
    window->draw(tagline);
    window->draw(start);
    window->display();

}

void MenuScreen::interpretInput(){

}

