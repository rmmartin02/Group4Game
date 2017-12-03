//
// Created by Ruoying Hao on 12/3/17.
//

#include "Screens/TimeoutScreen.hpp"
TimeoutScreen::TimeoutScreen(){
    //background
    if (!background.loadFromFile("../resource/background/timeout_background.jpg"))
    {
        // error...
    }
    bg.setTexture(background);

    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    tagline.setFont(textFont);

    tagline.setString("You ran out of time..");
    tagline.setFillColor(sf::Color::White);
    tagline.setCharacterSize(36);
    tagline.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - tagline.getLocalBounds().width/2, 200));


}

void TimeoutScreen::render(sf::RenderWindow *window){
    window->clear();
    window->draw(bg);
    window->draw(tagline);
    window->display();

}
void TimeoutScreen::interpretInput(std::vector<sf::Event>& events){

}