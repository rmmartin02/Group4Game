//
// Created by Ruoying Hao on 12/6/17.
//
#include "Screens/WinScreen.hpp"
WinScreen::WinScreen(){
    if (!background.loadFromFile("../resource/background/win_background.jpg"))
    {
        // error...
    }
    bg.setTexture(background);
    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    message.setFont(textFont);
    message.setString("          Woohoo! Mission Acomplished!\n"
                       "You directed the missile to hit an enemy ship!");
    message.setCharacterSize(35);
    message.setFillColor(sf::Color::White);
    message.setPosition(sf::Vector2f(SCREEN_WIDTH/2-message.getLocalBounds().width/2,250));

    enter.setFont(textFont);
    enter.setString("Press Space to Return to Menu");
    enter.setCharacterSize(30);
    enter.setFillColor(sf::Color::White);
    enter.setPosition(sf::Vector2f(SCREEN_WIDTH/2-enter.getLocalBounds().width/2,250+message.getLocalBounds().height+30));



}

void WinScreen::render(sf::RenderWindow *window){
    window->clear();
    window->draw(bg);

    window->draw(message);
    //window->draw(enter);
    window->display();

}
void WinScreen::interpretInput(std::vector<sf::Event>& events){

}
