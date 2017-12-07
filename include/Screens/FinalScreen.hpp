//
// Created by Ruoying Hao on 12/7/17.
//

#ifndef FINALSCREEN_HPP
#define FINALSCREEN_HPP
#include "Global.hpp"
#include "Screens/Screen.hpp"
#include <sstream>
#include <fstream>
#include <string>

class FinalScreen : public Screen {
public:
    FinalScreen();
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

#endif //FINALSCREEN_HPP
