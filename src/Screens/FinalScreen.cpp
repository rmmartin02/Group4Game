//
// Created by Ruoying Hao on 12/7/17.
//

#include "Screens/FinalScreen.hpp"

FinalScreen::FinalScreen(){
    if (!background.loadFromFile("../resource/background/final_background.jpg"))
    {
        // error...
    }
    bg.setTexture(background);
    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    message.setFont(textFont);

    message.setString("You have reached the missile!\n"
                              " Now Hack the Missile!");



    message.setCharacterSize(50);
    message.setFillColor(sf::Color::White);
    message.setPosition(sf::Vector2f(SCREEN_WIDTH/2-message.getLocalBounds().width/2,200));

    enter.setFont(textFont);
    enter.setString("Press Space to hack");
    enter.setCharacterSize(30);
    enter.setFillColor(sf::Color::White);
    enter.setPosition(sf::Vector2f(SCREEN_WIDTH/2-enter.getLocalBounds().width/2,200+message.getLocalBounds().height+30));



}

void FinalScreen::render(sf::RenderWindow *window){
    window->clear();
    window->draw(bg);

    window->draw(message);
    window->draw(enter);
    window->display();

}
void FinalScreen::interpretInput(std::vector<sf::Event>& events){

}