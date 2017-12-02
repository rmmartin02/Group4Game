//
// Created by Arman Franco on 11/25/17.
//

#include "Screens/MiniGameScreen.hpp"
#include <vector>

//const std::string MiniGameScreen::bg = "../MiniGame/circuit-board.png";



void MiniGameScreen::setPuzzle(int size, int numberOfEmptySlots) {

    difficulty = size;

    puzzle.setCurrentBoard(size);
    puzzle.setToInitialState(numberOfEmptySlots);

}

MiniGameScreen::MiniGameScreen() {
    //background
    if (!background.loadFromFile("../src/MiniGame/minigame-bg.jpg")) {
        // error...
    }
    bg.setTexture(background);

    two_sheet.loadFromFile("../src/MiniGame/laser.png");
}

std::vector<sf::Sprite> MiniGameScreen::createSpriteBoard(int difficulty) {

    std::vector<sf::Sprite> tiles(difficulty * difficulty);

    if (difficulty == 2) {

        int sheet_xMax = two_sheet.getSize().x;
        int sprite_size = 300;

        int x = 0;
        int y = 0;

        int x_pos = 100;
        int y_pos = 0;

        for (int i = 0; i < 4; i++) {

            sf::Sprite sprite(two_sheet,sf::IntRect(x,y,300,300));

            tiles[i] = sprite;

            tiles[i].setPosition(x_pos,y_pos);

            if (x != sheet_xMax/2) {
                x += sprite_size;
                x_pos += sprite_size;

            } else if (x == sheet_xMax/2) {
                x = 0;
                y += sprite_size;

                x_pos = 100;
                y_pos += sprite_size;
            }
        }

        spriteBoardCreated = true;
        return tiles;

    }

}

std::vector<sf::Sprite> MiniGameScreen::orderSpriteBoard(std::vector<sf::Sprite> spriteBoard) {

    std::vector<sf::Sprite> tiles = spriteBoard;
    std::vector<sf::Sprite> finalTiles(4);

    if (difficulty == 2) {

        int sheet_xMax = 600;
        int sheet_yMax = 600;
        int sprite_size = 300;

        int x_pos = 100;
        int y_pos = 0;
        int count = 0;

        for (int i = 0; i < 2; i++) {

            for (int m = 0; m < 2; m ++) {

                int y = shuffledPuzzle.getValue(i,m); //change back to shuffledboard

                tiles[y].setPosition(x_pos,y_pos);

                finalTiles[y] = tiles[y];

                count ++;

                if (x_pos < 400) {
                    x_pos += 300;
                } else if (x_pos == 400) {
                    x_pos = 100;
                    y_pos += 300;
                }

            }


        }

        tilesOrdered = true;
        return finalTiles;

    }

}


MiniGameScreenBackend MiniGameScreen::shufflePuzzle(MiniGameScreenBackend unshuffledPuzzle, int pathLength) {

    shuffled = true;
    return unshuffledPuzzle.shuffleBoard(pathLength);

}

void MiniGameScreen::moveOnClick(MiniGameScreenBackend puzzle, sf::Vector2<float> coordinates, sf::RenderWindow* window) {

    int row;
    int column;

    if (tiles[0].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 0;
        column = 0;

        //std::cout << "Tile 1 hit" << std::endl;
    } else

    if (tiles[1].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 0;
        column = 1;

        //std::cout << "Tile 2 hit" << std::endl;
    } else

    if (tiles[2].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 1;
        column = 0;

        //std::cout << "Tile 3 hit" << std::endl;
    } else

    if (tiles[3].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 1;
        column = 1;

        //std::cout << "Tile 4 hit" << std::endl;
    }


    std::cout << "Row is: " << row << " Column is: "<< column << std::endl;

    if (row == 1 && column == 1) {
        std::cout << "Move 4th tile" << std::endl;
        //
        //std::cout << std::endl;

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);
            //std::cout << "Moved up succesffuly" << std::endl;
        }

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);
    } else

    if (row == 0 && column == 0) {
        std::cout << "Move 1st tile" << std::endl;
        //std::cout << "Tile to right's value is: " << this->puzzle.getValue(row+1, column+1) << std::endl;

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);

        }
    } else

    if (row == 0 && column == 1) {
        std::cout << "Move 2nd tile" << std::endl;

        //std::cout << "Tile below's value is: " << this->shuffledPuzzle.getValue(row + 1, column) << std::endl;

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0) {
            //std::cout << "value before op is: " << this->shuffledPuzzle.getValue(row, column) << std::endl;
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);
            //std::cout << "value after op is: " << this->shuffledPuzzle.getValue(row, column) << std::endl;

        }

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);
    } else

    if (row == 1 && column == 0) {
        std::cout << "Move 3rd tile" << std::endl;

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);
            std::cout << "MOVED RIGHT" << std::endl;

        }
    }

}

void MiniGameScreen::render(sf::RenderWindow *window) {

    int difficulty = 2;

    if (!spriteBoardCreated) {

        tiles = createSpriteBoard(difficulty);

        std::cout << "sprite board created" << std::endl;

    }


    window->clear();
    window->draw(bg);

    MiniGameScreen::setPuzzle(2,1);

    if (!shuffled) {

        shuffledPuzzle = MiniGameScreen::shufflePuzzle(puzzle,1);

        std::cout << "shuffled" << std::endl;

    }

    if (!tilesOrdered)
        orderedTiles = MiniGameScreen::orderSpriteBoard(tiles);
    else
        orderedTiles = MiniGameScreen::orderSpriteBoard(orderedTiles);


    for (int i = 0; i < difficulty; i ++) {
        for (int m = 0; m < difficulty; m ++) {

            std::cout << "value is: " << shuffledPuzzle.getValue(i,m) << std::endl;

            window->draw(orderedTiles[puzzle.getValue(i,m)]);

        }

    }

    //std::cout << std::endl;

    sf::Texture grid;
    grid.loadFromFile("../src/MiniGame/two_grid.png");
    sf::Sprite gridSprite;
    gridSprite.setPosition(100,0);
    gridSprite.setTexture(grid);

    window->draw(gridSprite);
    window->display();

}

void MiniGameScreen::interpretInput(){

}