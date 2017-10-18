//
// Created by Ruoying Hao on 10/17/17.
//

#include "../include/Game.hpp"
#include <SFML/Graphics.hpp>
#include "DEFINITION.hpp"
//#include "Screens/Screen.hpp"
//#include "Screens/MenuScreen.hpp"

//MenuScreen menuScreen;

Game::Game(){
    window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Agent P: Infiltration");
    //background
    if (!background.loadFromFile("../resource/background/start_background.jpg"))
    {
        // error...
    }

    bg.setTexture(background);



    //logo

    if (!logo.loadFromFile("../resource/API.png"))
    {
        // error...
    }
    logo_sprite.setTexture(logo);
    logo_sprite.setScale(LOGO_SCALE,LOGO_SCALE);
    logo_sprite.setPosition(SCREEN_WIDTH/2 - 476*LOGO_SCALE,100);


    //tagline

    if (!taglineFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    tagline.setFont(taglineFont);

    tagline.setString("You Have 10 Minutes, Save the Earth.");
    tagline.setFillColor(sf::Color::White);
    tagline.setCharacterSize(36);
    tagline.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - tagline.getLocalBounds().width/2, SCREEN_HEIGHT/2.5));



    //start button

    start.setSize(sf::Vector2f(200, 50));
    start.setOutlineColor(sf::Color::White);
    start.setFillColor(sf::Color::Transparent);
    start.setOutlineThickness(5);
    start.setPosition(SCREEN_WIDTH/2 - start.getLocalBounds().width/2, SCREEN_HEIGHT/2);



}
Game::~Game()
{
}

void Game::Loop() {
    window.clear();
    while (window.isOpen()) {
        // process events
        sf::Event Event;
        while (window.pollEvent(Event)) {
            // Exit
            if (Event.type == sf::Event::Closed)
                window.close();
        }

        //menuScreen.render(&window);

        window.draw(bg);
        window.draw(logo_sprite);
        window.draw(tagline);
        window.draw(start);
        window.display();
    }
}