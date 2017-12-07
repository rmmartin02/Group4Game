//
// Created by Ruoying Hao on 12/6/17.
//

#ifndef TRANSITSCREEN_HPP
#define TRANSITSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"
#include <sstream>
#include <fstream>
#include <string>

class TransitScreen : public Screen {
public:
    TransitScreen();
    void render(sf::RenderWindow *window) override;
    void interpretInput(std::vector<sf::Event>& events) override;
    bool finalState=false;
private:
    sf::Texture background;
    sf::Sprite bg;
    sf::Font textFont;
    sf::Text message;
    sf::Text enter;
};

#endif //TRANSITSCREEN_HPP
