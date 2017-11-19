#include "Screens/ControlsScreen.hpp"

ControlsScreen::ControlsScreen(){
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
    logo_sprite.setPosition(SCREEN_WIDTH/2 - 476*LOGO_SCALE,50);


    //tagline

    if (!textFont.loadFromFile("../resource/fonts/Adventure.otf"))
    {
        // error...
    }
    tagline.setFont(textFont);

    tagline.setString("Rebind Controls");
    tagline.setFillColor(sf::Color::White);
    tagline.setCharacterSize(36);
    tagline.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - tagline.getLocalBounds().width/2, logo_sprite.getPosition().y + logo_sprite.getLocalBounds().height - 20));



    //back
    back.setFont(textFont);
    back.setString("Back");
    back.setFillColor(sf::Color::White);
    back.setCharacterSize(30);
    back.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - back.getLocalBounds().width/2, SCREEN_HEIGHT-back.getLocalBounds().height-40));

    keys[0] = sf::Keyboard::Up;
    keys[1] = sf::Keyboard::Down;
    keys[2] = sf::Keyboard::Left;
    keys[3] = sf::Keyboard::Right;
    loadKeys();

    //have some sort of "selected" variable, change color of that option and put arrow next to it
    up_text.setFont(textFont);
    up_text.setString("Up: " + key_strings[keys[0]+1]);
    up_text.setFillColor(sf::Color::White);
    up_text.setCharacterSize(30);
    up_text.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - up_text.getLocalBounds().width/2, tagline.getPosition().y+tagline.getLocalBounds().height+30));

    down_text.setFont(textFont);
    down_text.setString("Down: " + key_strings[keys[1]+1]);
    down_text.setFillColor(sf::Color::White);
    down_text.setCharacterSize(30);
    down_text.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - down_text.getLocalBounds().width/2, up_text.getPosition().y+up_text.getLocalBounds().height+30));

    left_text.setFont(textFont);
    left_text.setString("Left: " + key_strings[keys[2]+1]);
    left_text.setFillColor(sf::Color::White);
    left_text.setCharacterSize(30);
    left_text.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - left_text.getLocalBounds().width/2, down_text.getPosition().y+down_text.getLocalBounds().height+30));

    right_text.setFont(textFont);
    right_text.setString("Right: " + key_strings[keys[3]+1]);
    right_text.setFillColor(sf::Color::White);
    right_text.setCharacterSize(30);
    right_text.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - right_text.getLocalBounds().width/2, left_text.getPosition().y+left_text.getLocalBounds().height+30));

    control_options[0] = &up_text;
    control_options[1] = &down_text;
    control_options[2] = &left_text;
    control_options[3] = &right_text;
    control_options[4] = &back;
    control_options[highlighted]->setFillColor(sf::Color::Green);
}

void ControlsScreen::render(sf::RenderWindow *window){
    window->clear();
    window->draw(bg);
    window->draw(logo_sprite);
    window->draw(tagline);
    window->draw(back);
    window->draw(up_text);
    window->draw(down_text);
    window->draw(left_text);
    window->draw(right_text);
    window->display();

}

void ControlsScreen::interpretInput(std::vector<sf::Event>& events){
    for (auto event : events) {
        if (event.type == sf::Event::KeyPressed){
            if(selected==-1){
                if (event.key.code == sf::Keyboard::Up){
                    control_options[highlighted]->setFillColor(sf::Color::White);
                    //because c++ has a remainder operator NOT a modulus operator
                    if(highlighted==0)
                        highlighted = 3;
                    else
                        highlighted = (highlighted-1)%5;
                    control_options[highlighted]->setFillColor(sf::Color::Green);
                }
                if (event.key.code == sf::Keyboard::Down){
                    control_options[highlighted]->setFillColor(sf::Color::White);
                    highlighted = (highlighted+1)%5;
                    control_options[highlighted]->setFillColor(sf::Color::Green);
                }
                if (event.key.code == sf::Keyboard::Return){
                    selected = highlighted;
                    switch(selected){
                    case 0:
                        control_options[highlighted]->setString("Up: ");
                        break;
                    case 1:
                        control_options[highlighted]->setString("Down: ");
                        break;
                    case 2:
                        control_options[highlighted]->setString("Left: ");
                        break;
                    case 3:
                        control_options[highlighted]->setString("Right: ");
                        break;
                    case 4:
                        break;
                }
                }
            }
            else{
                //change selected key to pressed key
                keys[selected] = event.key.code;
                switch(selected){
                    case 0:
                        control_options[selected]->setString("Up: " + key_strings[keys[0]+1]);
                        break;
                    case 1:
                        control_options[selected]->setString("Down: " + key_strings[keys[1]+1]);
                        break;
                    case 2:
                        control_options[selected]->setString("Left: " + key_strings[keys[2]+1]);
                        break;
                    case 3:
                        control_options[selected]->setString("Right: " + key_strings[keys[3]+1]);
                        break;
                }
                selected = -1;
            }
        }
    }
}

bool ControlsScreen::saveKeys(){
    std::ofstream myfile ("../resource/keyBindings.txt");
    if (myfile.is_open()){
        myfile << keys[0] << "\n";
        myfile << keys[1] << "\n";
        myfile << keys[2] << "\n";
        myfile << keys[3] << "\n";
        myfile.close();
        return true;
    }
    else std::cout << "ControlsScreen: Unable to save to keybindings file";
    return false;
}

bool ControlsScreen::loadKeys(){
    //std::cout << "ControlsScreen: loading keys\n";
    std::string line;
    std::ifstream myfile("../resource/keyBindings.txt");
    if ( !myfile.is_open() ) {
        std::cout << "ControlsScreen: Failed to open keyBindings.txt" << std::endl;
        return false;
    }
    int i = 0;
    while ( getline (myfile,line) )
    {
      //std::cout << line << '\n';
      keys[i] = sf::Keyboard::Key(std::stoi(line));
      i += 1;
    }
    myfile.close();
    return true;
}

int ControlsScreen::getHighlighted(){
    return highlighted;
}

void ControlsScreen::resetHighlighted(){
    highlighted = 0;
}
