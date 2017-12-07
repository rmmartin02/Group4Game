//
// Created by Arman Franco on 11/25/17.
//

#include "Screens/MiniGameScreen.hpp"

//const std::string MiniGameScreen::bg = "../MiniGame/circuit-board.png";





MiniGameScreen::MiniGameScreen() {

    //Background
    if (!background.loadFromFile("../resource/MiniGame/minigame-bg.jpg")) {
        // error...
    }
    bg.setTexture(background);

    //Sprite Sheet
    three_sheet.loadFromFile("../resource/MiniGame/laser3ez.png");

    //Win Screen
    if (!winScreen.loadFromFile("../resource/MiniGame/winscreen.png")) {
        // error...
    }
    winScreenSprite.setTexture(winScreen);

    //Sliding Sound
    bufferSlide.loadFromFile("../resource/MiniGame/click.flac");
    slideSound.setBuffer(bufferSlide);


}

void MiniGameScreen::setPuzzle(int size, int numberOfEmptySlots) {
    difficulty = size;

    puzzle.setCurrentBoard(size);
    puzzle.setToInitialState(numberOfEmptySlots);

}

std::vector<sf::Sprite> MiniGameScreen::createSpriteBoard(int difficulty) {

    std::vector<sf::Sprite> tiles(difficulty * difficulty);

    if (difficulty == 3) {

        int sheet_xMax = three_sheet.getSize().x;
        int sprite_size = 200;

        int x = 0;
        int y = 0;

        int x_pos = 100;
        int y_pos = 0;

        for (int i = 0; i < difficulty * difficulty; i++) {

            sf::Sprite sprite(three_sheet,sf::IntRect(x,y,sprite_size,sprite_size));

            tiles[i] = sprite;

            //tiles[i].setPosition(x_pos,y_pos);

            if (x != sheet_xMax - sprite_size) {
                x += sprite_size;
                x_pos += sprite_size;

            } else if (x == sheet_xMax - sprite_size) {
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

//std::vector<sf::Sprite> MiniGameScreen::orderSpriteBoard(std::vector<sf::Sprite>& spriteBoard, MiniGameScreenBackend puzzleIn) {
void MiniGameScreen::orderSpriteBoard(std::vector<sf::Sprite>& spriteBoard, MiniGameScreenBackend puzzleIn) {

    //std::vector<sf::Sprite> tiles = spriteBoard;
    //std::vector<sf::Sprite> finalTiles(difficulty * difficulty);

    if (difficulty == 3) {

        int sheet_xMax = 600;
        int sheet_yMax = 600;
        int sprite_size = 200;

        int x_pos = 100;
        int y_pos = 0;
        int count = 0;

        for (int i = 0; i < difficulty; i++) {

            for (int m = 0; m < difficulty; m ++) {

                int y = puzzleIn.getValue(i,m);

                if (y == 0)
                    y = 9;

                spriteBoard[y-1].setPosition(x_pos,y_pos);
                //MIDIFIED THIS, ORIGINAL:
                //finalTiles[y-1] = spriteBoard[y-1]; //uncomment

                count ++;

                if (x_pos < 100 + sprite_size*2) {
                    x_pos += sprite_size;
                } else if (x_pos == 100 + sprite_size*2) {
                    x_pos = 100;
                    y_pos += sprite_size;
                }

            }


        }

        tilesOrdered = true;
        //std::cout<<"MINIGAMESCREEN 129\n";
      //  return spriteBoard; //change back to finaltiles

    }

}

bool MiniGameScreen::checkWinStatus(MiniGameScreenBackend solvedPuzzle, MiniGameScreenBackend currentPuzzle) {

    for (int i = 0; i < difficulty; i++) {
        for (int m = 0; m < difficulty; m ++) {

            if (solvedPuzzle.getValue(i,m) != currentPuzzle.getValue(i,m))
                return false;

        }
    }

    gameWon = true;
    return true;
}

MiniGameScreenBackend MiniGameScreen::shufflePuzzle(MiniGameScreenBackend unshuffledPuzzle, int pathLength) {

    shuffled = true;
    return unshuffledPuzzle.shuffleBoard(pathLength);

}

int MiniGameScreen::moveOnClick(MiniGameScreenBackend puzzle, sf::Vector2<float> coordinates, sf::RenderWindow* window) {

    int row;
    int column;
    int sprite_size = 200;

    if (tiles[0].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[0].getPosition().x - 100)/sprite_size;
        if (tiles[0].getPosition().y != 0)
            row = tiles[0].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 1 hit" << std::endl;

    } else

    if (tiles[1].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[1].getPosition().x - 100)/sprite_size;
        if (tiles[1].getPosition().y != 0)
            row = tiles[1].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 2 hit" << std::endl;
    } else

    if (tiles[2].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[2].getPosition().x - 100)/sprite_size;
        if (tiles[2].getPosition().y != 0)
            row = tiles[2].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 3 hit" << std::endl;
    } else

    if (tiles[3].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[3].getPosition().x - 100)/sprite_size;
        if (tiles[3].getPosition().y != 0)
            row = tiles[3].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 4 hit" << std::endl;
    } else

    if (tiles[4].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[4].getPosition().x - 100)/sprite_size;
        if (tiles[4].getPosition().y != 0)
            row = tiles[4].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 5 hit" << std::endl;
    } else

    if (tiles[5].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[5].getPosition().x - 100)/sprite_size;
        if (tiles[5].getPosition().y != 0)
            row = tiles[5].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 6 hit" << std::endl;
    } else

    if (tiles[6].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[6].getPosition().x - 100)/sprite_size;
        if (tiles[6].getPosition().y != 0)
            row = tiles[6].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 7 hit" << std::endl;
    } else

    if (tiles[7].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[7].getPosition().x - 100)/sprite_size;
        if (tiles[7].getPosition().y != 0)
            row = tiles[7].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 8 hit" << std::endl;
    } else

    if (tiles[8].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        column = (tiles[8].getPosition().x - 100)/sprite_size;
        if (tiles[8].getPosition().y != 0)
            row = tiles[8].getPosition().y/sprite_size;
        else
            row = 0;

        //std::cout << "Tile 9 hit" << std::endl;
    }else{
        return -1;
    }

    // NOW MOVE!!
    slideSound.play();

    if (row == 2 && column == 2) {
        //std::cout << "Move 4th tile" << std::endl;
        //
        ////std::cout << std::endl;

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);
            ////std::cout << "Moved up successfully" << std::endl;
        }

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);
    } else

    if (row == 0 && column == 0) {
        //std::cout << "Move 1st tile" << std::endl;
        ////std::cout << "Tile to right's value is: " << this->puzzle.getValue(row+1, column+1) << std::endl;

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);

        }
    } else

    if (row == 0 && column == 2) {
        //std::cout << "Move 2nd tile" << std::endl;

        ////std::cout << "Tile below's value is: " << this->shuffledPuzzle.getValue(row + 1, column) << std::endl;

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0) {
            ////std::cout << "value before op is: " << this->shuffledPuzzle.getValue(row, column) << std::endl;
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);
            ////std::cout << "value after op is: " << this->shuffledPuzzle.getValue(row, column) << std::endl;

        }

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);
    } else

    if (row == 2 && column == 0) {
        //std::cout << "Move 3rd tile" << std::endl;

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);
            //std::cout << "MOVED RIGHT" << std::endl;

        }
    } else

    if (row == 1 && column == 1) {

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);
            //std::cout << "MOVED RIGHT" << std::endl;

        }
        if (this->shuffledPuzzle.getValue(row + 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);
    } else

    if (column == 0) {

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);
            //std::cout << "MOVED RIGHT" << std::endl;

        }
        if (this->shuffledPuzzle.getValue(row + 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);
    } else

    if (column == 2) {

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);
    } else

    if (row == 0) {

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);
            //std::cout << "MOVED RIGHT" << std::endl;

        }

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);
    } else

    if (row == 2) {

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);
            //std::cout << "MOVED RIGHT" << std::endl;

        }
    }




    /**
    for (int i = 0; i < difficulty * difficulty; i ++) {

        if (orderedTiles[i].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {

        }

    }
     **/

    /**
    if (tiles[0].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 0;
        column = 0;

        ////std::cout << "Tile 1 hit" << std::endl;
    } else

    if (tiles[1].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 0;
        column = 1;

        ////std::cout << "Tile 2 hit" << std::endl;
    } else

    if (tiles[2].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 1;
        column = 0;

        ////std::cout << "Tile 3 hit" << std::endl;
    } else

    if (tiles[3].getGlobalBounds().contains(window->mapPixelToCoords(sf::Vector2i(coordinates)))) {
        row = 1;
        column = 1;

        ////std::cout << "Tile 4 hit" << std::endl;
    }
     **/

    //std::cout << "Row is: " << row << " Column is: "<< column << std::endl;

    /**
    if (row == 1 && column == 1) {
        //std::cout << "Move 4th tile" << std::endl;
        //
        ////std::cout << std::endl;

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);
            ////std::cout << "Moved up successfully" << std::endl;
        }

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);
    } else

    if (row == 0 && column == 0) {
        //std::cout << "Move 1st tile" << std::endl;
        ////std::cout << "Tile to right's value is: " << this->puzzle.getValue(row+1, column+1) << std::endl;

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);

        }
    } else

    if (row == 0 && column == 1) {
        //std::cout << "Move 2nd tile" << std::endl;

        ////std::cout << "Tile below's value is: " << this->shuffledPuzzle.getValue(row + 1, column) << std::endl;

        if (this->shuffledPuzzle.getValue(row + 1, column) == 0) {
            ////std::cout << "value before op is: " << this->shuffledPuzzle.getValue(row, column) << std::endl;
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEDOWN);
            ////std::cout << "value after op is: " << this->shuffledPuzzle.getValue(row, column) << std::endl;

        }

        if (this->shuffledPuzzle.getValue(row, column - 1) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVELEFT);
    } else

    if (row == 1 && column == 0) {
        //std::cout << "Move 3rd tile" << std::endl;

        if (this->shuffledPuzzle.getValue(row - 1, column) == 0)
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVEUP);

        if (this->shuffledPuzzle.getValue(row, column + 1) == 0) {
            this->shuffledPuzzle = this->shuffledPuzzle.move(row, column, MiniGameScreenBackend::MOVERIGHT);
            //std::cout << "MOVED RIGHT" << std::endl;

        }
    }
    **/
return 0;

}

void MiniGameScreen::render(sf::RenderWindow *window) {

    int difficulty = 3;

    if (!spriteBoardCreated) {

        tiles = createSpriteBoard(difficulty);

        //std::cout << "sprite board created" << std::endl;

    }


    window->clear();
    window->draw(bg);

    MiniGameScreen::setPuzzle(3,1);

    if (!shuffled) {

        //set second parameter to zero to NOT shuffle
        // 40 is a good diff

        shuffledPuzzle = MiniGameScreen::shufflePuzzle(puzzle,shuffleLengthVar);

        //std::cout << "shuffled" << std::endl;

    }


    if (!tilesOrdered){
      //std::cout<<"MINIGAME REACHED 525\n";
      //orderedTiles = MiniGameScreen::orderSpriteBoard(tiles, puzzle);
      MiniGameScreen::orderSpriteBoard(tiles, puzzle);
      //std::cout<<"MINIGAME REACHED 527\n";
    }

    else{

      //orderedTiles = MiniGameScreen::orderSpriteBoard(orderedTiles, shuffledPuzzle);
      MiniGameScreen::orderSpriteBoard(tiles, shuffledPuzzle);

    }





    for (int i = 0; i < difficulty; i ++) {
        for (int m = 0; m < difficulty; m ++) {

            //std::cout << "value is: " << shuffledPuzzle.getValue(i,m) << std::endl;


          //  window->draw(orderedTiles[shuffledPuzzle.getValue(i,m)]);
          window->draw(tiles[shuffledPuzzle.getValue(i,m)]);

        }

    }

    ////std::cout << std::endl;

    sf::Texture grid;
    grid.loadFromFile("../resource/MiniGame/three_grid.png");
    sf::Sprite gridSprite;
    gridSprite.setPosition(100,0);
    gridSprite.setTexture(grid);

    window->draw(gridSprite);

    MiniGameScreen::checkWinStatus(puzzle, shuffledPuzzle);

    if (gameWon) {
        window->draw(winScreenSprite);
    }

    window->display();

}

void MiniGameScreen::interpretInput(std::vector<sf::Event>& events){
    
}

void MiniGameScreen::setShuffleLength(int len){
  shuffleLengthVar=len;
}

void MiniGameScreen::setMinigameFinal(){
    isFinal=true;
}

bool MiniGameScreen::getMinigameFinal(){
        return isFinal;
}