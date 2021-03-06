//
// Created by Arman Franco on 11/25/17.
//

#ifndef CSCI437_MINIGAMESCREEN_HPP
#define CSCI437_MINIGAMESCREEN_HPP
#include "Global.hpp"
#include "Screens/Screen.hpp"
#include "Screens/GameScreen.hpp"
#include "Logic.hpp"
#include <vector>
#include "MiniGame/MiniGameBackend.hpp"

class MiniGameScreen : public Screen {

public:


    MiniGameScreen(Logic *logic);

    Logic* logic_;

    bool shuffled = false;

    bool spriteBoardCreated = false;

    bool tilesOrdered= false;

    bool gameWon = false;

    bool checkWinStatus (MiniGameScreenBackend solvedPuzzle, MiniGameScreenBackend currentPuzzle);

    std::vector<sf::Sprite> tiles;

    std::vector<sf::Sprite> orderedTiles;

    MiniGameScreenBackend shufflePuzzle (MiniGameScreenBackend unshuffledPuzzle, int pathLenth);

    int moveOnClick(MiniGameScreenBackend puzzle, sf::Vector2<float> coordinates, sf::RenderWindow* window);

    MiniGameScreenBackend puzzle;

    MiniGameScreenBackend shuffledPuzzle;

    sf::Texture background;

    sf::Texture three_sheet;

    sf::Sprite bg;

    sf::Texture winScreen;

    sf::Sprite winScreenSprite;

    sf::SoundBuffer bufferSlide;

    sf::Sound slideSound;

    int difficulty;

    void setPuzzle(int size, int numberOfEmptySlots);

    void interpretInput(std::vector<sf::Event>& events) override;

    std::vector<sf::Sprite> createSpriteBoard(int difficulty);

  //  std::vector<sf::Sprite> orderSpriteBoard(std::vector<sf::Sprite> spriteBoard, MiniGameScreenBackend puzzleIn);
    void orderSpriteBoard(std::vector<sf::Sprite>& spriteBoard, MiniGameScreenBackend puzzleIn);

    void render(sf::RenderWindow *window) override;

    int shuffleLengthVar;

    void setShuffleLength(int len);

    void setMinigameFinal();

    bool getMinigameFinal();

    bool isFinal=false;

    void renderTimeLeft(sf::RenderWindow *window);

    sf::Font text_font;
    sf::Text time_left_text;
    sf::RectangleShape time_left_background;
    float time_left_width;



private:

    //Logic* logic_;



};


#endif //CSCI437_MINIGAMESCREEN_HPP
