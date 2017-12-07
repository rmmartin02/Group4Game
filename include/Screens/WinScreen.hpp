//
// Created by Ruoying Hao on 12/6/17.
//

#ifndef WINSCREEN_HPP
#define WINSCREEN_HPP
#include "Global.hpp"
#include "Screens/Screen.hpp"
#include <sstream>
#include <fstream>
#include <string>
class WinScreen : public Screen {
public:
    WinScreen();
    void render(sf::RenderWindow *window) override;
    void interpretInput(std::vector<sf::Event>& events) override;
private:
    sf::Texture background;
    sf::Sprite bg;
    sf::Font textFont;
    sf::Text message;
    sf::Text enter;
};
#endif //WINSCREEN_HPP
