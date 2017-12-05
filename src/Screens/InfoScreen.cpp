//
// Created by Ruoying Hao on 12/4/17.
//
#include "Screens/InfoScreen.hpp"
InfoScreen::InfoScreen(){
    if (!background.loadFromFile("../resource/background/start_background.jpg"))
    {
        // error...
    }
    bg.setTexture(background);
    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    story.setFont(textFont);
    rules.setFont(textFont);
    controls.setFont(textFont);
    back.setFont(textFont);


    story.setString("    In 2027,the tension between humans and the aliens is high. It seems that\n"
                    "a war could happen any day. Agent P is a human spy, positioning in an \n"
                    "alien spacecraft that carries a very destructive missile, gathering highly \n"
                    "classified intelligence information to aid the human side.\n"
                    "    One day, Agent P received an emergency message from Earth. It turns \n"
                    "out that the aliens are planning a secret missile attack targeting Earth.\n"
                    "Agent P has 10 minutes to infiltrate layers of heavily guarded spacecraft\n"
                    "regions in order to reach a secret room, where he can have the opport-\n"
                    "unity to redirect the missile to stop the attack.");
    story.setFillColor(sf::Color::White);
    story.setCharacterSize(25);
    story.setPosition(20,20);

    rules.setString("As Agent P, you have 10 minutes to disable the missile. You should avoid\n"
                    "being detected by the lasers and aliens in the spacecraft.\n"
                    "Getting detected by the laser would get aliens alerted. When an alien\n"
                    "catches you, you could hack them. Hacking is a process of solving a\n"
                    "sliding puzzle on the screen.");
    rules.setCharacterSize(25);
    rules.setFillColor(sf::Color::White);
    rules.setPosition(20,320);

    controls.setString("By Default, use arrow keys to move around, use mouse to hack.");
    controls.setCharacterSize(25);
    controls.setFillColor(sf::Color::White);
    controls.setPosition(20,480);

    back.setString("Back");
    back.setCharacterSize(40);
    back.setPosition(sf::Vector2f(SCREEN_WIDTH/2-back.getLocalBounds().width/2,530));
    back.setFillColor(sf::Color::Green);


}

void InfoScreen::render(sf::RenderWindow *window){
    window->clear();
    window->draw(bg);
    window->draw(story);
    window->draw(rules);
    window->draw(controls);
    window->draw(back);
    window->display();

}
void InfoScreen::interpretInput(std::vector<sf::Event>& events){
    for (auto event : events) {

    }


}

