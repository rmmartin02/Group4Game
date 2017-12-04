//
// Created by Arman Franco on 11/25/17.
//

#ifndef CSCI437_MINIGAMESCREEN_HPP
#define CSCI437_MINIGAMESCREEN_HPP

#include "Screens/Screen.hpp"
#include "Logic.hpp"
#include "../src/MiniGame/MiniGameBackend.hpp"

class MiniGameScreen : public Screen {

public:


    MiniGameScreen();

    bool shuffled = false;

    bool spriteBoardCreated = false;

    bool tilesOrdered= false;

    bool gameWon = false;

    bool checkWinStatus (MiniGameScreenBackend solvedPuzzle, MiniGameScreenBackend currentPuzzle);

    std::vector<sf::Sprite> tiles;

    std::vector<sf::Sprite> orderedTiles;

    MiniGameScreenBackend shufflePuzzle (MiniGameScreenBackend unshuffledPuzzle, int pathLenth);

    void moveOnClick(MiniGameScreenBackend puzzle, sf::Vector2<float> coordinates, sf::RenderWindow* window);

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

    std::vector<sf::Sprite> orderSpriteBoard(std::vector<sf::Sprite> spriteBoard, MiniGameScreenBackend puzzleIn);

    void render(sf::RenderWindow *window) override;



private:

    Logic* logic_;



};


#endif //CSCI437_MINIGAMESCREEN_HPP
