#include "Screens/ControlsScreen.hpp"

ControlsScreen::ControlsScreen(){
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
    logo_sprite.setPosition(SCREEN_WIDTH/2 - 476*LOGO_SCALE,50);


    //tagline

    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    tagline.setFont(textFont);

    tagline.setString("Rebind Controls");
    tagline.setFillColor(sf::Color::White);
    tagline.setCharacterSize(36);
    tagline.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - tagline.getLocalBounds().width/2, logo_sprite.getPosition().y + logo_sprite.getLocalBounds().height - 20));



    //back
    back.setFont(textFont);

    back.setString("Back [B]");
    back.setFillColor(sf::Color::White);
    back.setCharacterSize(30);
    back.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - back.getLocalBounds().width/2, SCREEN_HEIGHT-back.getLocalBounds().height-30));
    /*
    back.setSize(sf::Vector2f(200, 50));
    back.setOutlineColor(sf::Color::White);
    back.setFillColor(sf::Color::Transparent);
    back.setOutlineThickness(5);
    back.setPosition(SCREEN_WIDTH/2 - back.getLocalBounds().width/2, SCREEN_HEIGHT/2);
     */
    upText.setFont(textFont);

    upText.setString("Up:");
    upText.setFillColor(sf::Color::White);
    upText.setCharacterSize(30);
    upText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - upText.getLocalBounds().width/2, tagline.getPosition().y+tagline.getLocalBounds().height+30));

}

void ControlsScreen::render(sf::RenderWindow *window){
    //std::cout <<"render Menu Screen\n";
    window->clear();
    window->draw(bg);
    window->draw(logo_sprite);
    window->draw(tagline);
    window->draw(back);
    window->draw(upText);
    window->display();

}

void ControlsScreen::interpretInput(sf::Event event){

}

