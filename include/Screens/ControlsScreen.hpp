#ifndef CONTROLSSCREEN_HPP
#define CONTROLSSCREEN_HPP

#include "Global.hpp"
#include "Screens/Screen.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

class ControlsScreen : public Screen {
public:
	ControlsScreen();
	void render(sf::RenderWindow *window) override;
	void interpretInput(sf::Event event) override;


    //loads current key bindings
    bool loadKeys();

	bool saveKeys();

	std::string keyStrings[103] = { 
  "Unknown","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
  "Num0","Num1","Num2","Num3","Num4","Num5","Num6","Num7","Num8","Num9","Escape","LControl","LShift","LAlt",
  "LSystem","RControl","RShift","RAlt","RSystem","Menu","LBracket","RBracket","SemiColon","Comma","Period",
  "Quote","Slash","BackSlash","Tilde","Equal","Dash","Space","Return","BackSpace","Tab","PageUp","PageDown",
  "End","Home","Insert","Delete","Add","Subtract","Multiply","Divide","Left","Right","Up","Down","Numpad0",
  "Numpad1","Numpad2","Numpad3","Numpad4","Numpad5","Numpad6","Numpad7","Numpad8","Numpad9","F1","F2","F3",
  "F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15","Pause","KeyCount"};

private:
	sf::Texture background;
	sf::Sprite bg;
	sf::Sprite logo_sprite;
	sf::Texture logo;
	sf::Font textFont;
	sf::Text tagline;
	sf::Text back;

	sf::Text upText;
	sf::Text downText;
	sf::Text rightText;
	sf::Text leftText;

	sf::Text* controlOptions[4];
	int highlighted = 0;
	int selected = -1;

	sf::Keyboard::Key keys[4];
	//sf::RectangleShape back;
};

#endif // CONTROLSSCREEN_HPP

