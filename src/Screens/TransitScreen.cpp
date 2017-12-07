//
// Created by Ruoying Hao on 12/6/17.
//
#include "Screens/TransitScreen.hpp"
TransitScreen::TransitScreen(){
    if (!background.loadFromFile("../resource/background/transit_background.jpg"))
    {
        // error...
    }
    bg.setTexture(background);
    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    message.setFont(textFont);

    message.setString("You have reached the exit!\n"
                                  " But there's more to go");



    message.setCharacterSize(50);
    message.setFillColor(sf::Color::White);
    message.setPosition(sf::Vector2f(SCREEN_WIDTH/2-message.getLocalBounds().width/2,200));

    enter.setFont(textFont);
    enter.setString("Press Space to play the next level");
    enter.setCharacterSize(30);
    enter.setFillColor(sf::Color::White);
    enter.setPosition(sf::Vector2f(SCREEN_WIDTH/2-enter.getLocalBounds().width/2,200+message.getLocalBounds().height+30));



}

void TransitScreen::render(sf::RenderWindow *window){
    window->clear();
    window->draw(bg);

    window->draw(message);
    window->draw(enter);
    window->display();

}
void TransitScreen::interpretInput(std::vector<sf::Event>& events){

}
