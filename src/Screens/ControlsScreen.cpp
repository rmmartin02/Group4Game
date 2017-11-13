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
    back.setString("Back [B]");
    back.setFillColor(sf::Color::White);
    back.setCharacterSize(30);
    back.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - back.getLocalBounds().width/2, SCREEN_HEIGHT-back.getLocalBounds().height-30));

    keys[0] = sf::Keyboard::Up;
    keys[1] = sf::Keyboard::Down;
    keys[2] = sf::Keyboard::Left;
    keys[3] = sf::Keyboard::Right;
    loadKeys();

    //have some sort of "selected" variable, change color of that option and put arrow next to it
    upText.setFont(textFont);
    upText.setString("Up: " + keyStrings[keys[0]+1]);
    upText.setFillColor(sf::Color::White);
    upText.setCharacterSize(30);
    upText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - upText.getLocalBounds().width/2, tagline.getPosition().y+tagline.getLocalBounds().height+30));

    downText.setFont(textFont);
    downText.setString("Down: " + keyStrings[keys[1]+1]);
    downText.setFillColor(sf::Color::White);
    downText.setCharacterSize(30);
    downText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - downText.getLocalBounds().width/2, upText.getPosition().y+upText.getLocalBounds().height+30));

    leftText.setFont(textFont);
    leftText.setString("Left: " + keyStrings[keys[2]+1]);
    leftText.setFillColor(sf::Color::White);
    leftText.setCharacterSize(30);
    leftText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - leftText.getLocalBounds().width/2, downText.getPosition().y+downText.getLocalBounds().height+30));

    rightText.setFont(textFont);
    rightText.setString("Right: " + keyStrings[keys[3]+1]);
    rightText.setFillColor(sf::Color::White);
    rightText.setCharacterSize(30);
    rightText.setPosition(sf::Vector2f(SCREEN_WIDTH/2 - rightText.getLocalBounds().width/2, leftText.getPosition().y+leftText.getLocalBounds().height+30));

    controlOptions[0] = &upText;
    controlOptions[1] = &downText;
    controlOptions[2] = &leftText;
    controlOptions[3] = &rightText;
    controlOptions[highlighted]->setFillColor(sf::Color::Green);
}

void ControlsScreen::render(sf::RenderWindow *window){
    //std::cout <<"render Menu Screen\n";
    window->clear();
    window->draw(bg);
    window->draw(logo_sprite);
    window->draw(tagline);
    window->draw(back);
    window->draw(upText);
    window->draw(downText);
    window->draw(leftText);
    window->draw(rightText);
    window->display();

}

void ControlsScreen::interpretInput(sf::Event event){
    if (event.type == sf::Event::KeyPressed){
        if(selected==-1){
            if (event.key.code == sf::Keyboard::Up){
                controlOptions[highlighted]->setFillColor(sf::Color::White);
                //because c++ has a remainder operator NOT a modulus operator
                if(highlighted==0)
                    highlighted = 3;
                else
                    highlighted = (highlighted-1)%4;
                controlOptions[highlighted]->setFillColor(sf::Color::Green);
            }
            if (event.key.code == sf::Keyboard::Down){
                controlOptions[highlighted]->setFillColor(sf::Color::White);
                highlighted = (highlighted+1)%4;
                controlOptions[highlighted]->setFillColor(sf::Color::Green);
            }
            if (event.key.code == sf::Keyboard::Return){
                selected = highlighted;
            }
        }
        else{
            //change selected key to pressed key
            //keys[selected] = event.key.code;
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
    else std::cout << "Unable to open file";
    return false;;
}

bool ControlsScreen::loadKeys(){
    std::cout << "load keys\n";
    std::string line;
    std::ifstream myfile("../resource/keyBindings.txt");
    if ( !myfile.is_open() ) {
        std::cout << "Failed to open keyBindings.txt" << std::endl;
        return false;
    }
    int i = 0;
    while ( getline (myfile,line) )
    {
      std::cout << line << '\n';
      keys[i] = sf::Keyboard::Key(std::stoi(line));
      i += 1;
    }
    myfile.close();
    return true;
}