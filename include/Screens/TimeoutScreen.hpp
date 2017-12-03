//
// Created by Ruoying Hao on 12/3/17.
//

#ifndef TIMEOUTSCREEN_HPP
#define TIMEOUTSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"
class TimeoutScreen : public Screen {
public:
    TimeoutScreen();
    void render(sf::RenderWindow *window) override;
    void interpretInput(std::vector<sf::Event>& events) override;
private:
    sf::Texture background;
    sf::Sprite bg;

    sf::Font textFont;
    sf::Text tagline;

};

#endif //TIMEOUTSCREEN_HPP
