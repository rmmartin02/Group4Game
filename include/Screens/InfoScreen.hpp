//
// Created by Ruoying Hao on 12/4/17.
//

#ifndef INFOSCREEN_HPP
#define INFOSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"
#include <sstream>
#include <fstream>
#include <string>
class InfoScreen : public Screen {
public:
    InfoScreen();
    void render(sf::RenderWindow *window) override;
    void interpretInput(std::vector<sf::Event>& events) override;
private:
    sf::Texture background;
    sf::Sprite bg;
    sf::Font textFont;
    sf::Text story;
    sf::Text rules;
    sf::Text controls;
    sf::Text back;

};

#endif //CSCI437_INFOSCREEN_HPP
