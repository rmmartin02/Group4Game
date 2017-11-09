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

    //have some sort of "selected" variable, change color of that option and put arrow next to it
    upText.setFont(textFont);
    upText.setString("Up:");
    upText.setFillColor(sf::Color::White);
    upText.setCharacterSize(30);
    upText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - upText.getLocalBounds().width/2, tagline.getPosition().y+tagline.getLocalBounds().height+30));

    downText.setFont(textFont);
    downText.setString("Down:");
    downText.setFillColor(sf::Color::White);
    downText.setCharacterSize(30);
    downText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - downText.getLocalBounds().width/2, upText.getPosition().y+upText.getLocalBounds().height+30));

    leftText.setFont(textFont);
    leftText.setString("Left:");
    leftText.setFillColor(sf::Color::White);
    leftText.setCharacterSize(30);
    leftText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - leftText.getLocalBounds().width/2, downText.getPosition().y+downText.getLocalBounds().height+30));

    rightText.setFont(textFont);
    rightText.setString("Right:");
    rightText.setFillColor(sf::Color::White);
    rightText.setCharacterSize(30);
    rightText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - rightText.getLocalBounds().width/2, leftText.getPosition().y+leftText.getLocalBounds().height+30));

    controlOptions[0] = &upText;
    controlOptions[1] = &downText;
    controlOptions[2] = &leftText;
    controlOptions[3] = &rightText;
    controlOptions[highlighted]->setFillColor(sf::Color::Green);
}

void ControlsScreen::render(sf::RenderWindow *window){
    //std::cout <<"render Menu Screen\n";
    window->clear();
    window->draw(bg);
    window->draw(logo_sprite);
    window->draw(tagline);
    window->draw(back);
    window->draw(upText);
    window->draw(downText);
    window->draw(leftText);
    window->draw(rightText);
    window->display();

}

void ControlsScreen::interpretInput(sf::Event event){
    if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Up){
                controlOptions[highlighted]->setFillColor(sf::Color::White);
                //because c++ has a remainder operator NOT a modulus operator
                if(highlighted==0)
                    highlighted = 3;
                else
                    highlighted = (highlighted-1)%4;
                controlOptions[highlighted]->setFillColor(sf::Color::Green);
            }
            if (event.key.code == sf::Keyboard::Down){
                controlOptions[highlighted]->setFillColor(sf::Color::White);
                highlighted = (highlighted+1)%4;
                controlOptions[highlighted]->setFillColor(sf::Color::Green);
            }
            if (event.key.code == sf::Keyboard::Return){

            }
        }
}

