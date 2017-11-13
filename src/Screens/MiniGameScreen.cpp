//
// Created by Arman Franco on 10/27/17.
//

#include "Screens/MiniGameScreen.hpp"
#include <vector>

int boardSize;

enum class MiniGameScreen::Operation;

int pathLength;

MiniGameScreen::MiniGameScreen() {

    MiniGameScreen::Operation Operation;
    int pathLength = 0;
    MiniGameScreen parentBoard;
    std::vector<std::vector<int>> currentBoard;
    int boardSize;

};

std::vector<std::vector<int>> setCurrentBoard (int size) {

    boardSize = size;

    MiniGameScreen().currentBoard.resize(size);

    for (int i = 0; i < size; ++ i) {
        MiniGameScreen().currentBoard[i].resize(size);
    }

}

void setToInitialState(int numberOfEmptySlots) {

    std::vector<int> full_array(boardSize);
    std::vector<int> blank_array(boardSize);

    //int full_array [boardSize];
    //int blank_array [boardSize];

    int i = 1;
    int y;
    int blank_spaces = numberOfEmptySlots;
    int count = 0;

    for (y = 1; y <= boardSize; y += 1) {

        // CHECK IF FINAL ROW
        if (y == boardSize) {
            // NUMBER TILES EXCEPT BLANKS
            for (i = 1; i <= boardSize - blank_spaces; i += 1) {
                blank_array[i-1] = i + count;
            }
            // CREATE TEMPORARY ARRAY AND ADD IT TO FINAL BOARD
            std::vector<int> temp_array = blank_array;
            MiniGameScreen().currentBoard[y-1] = temp_array;
            count += boardSize;
        } else { // IF NOT FINAL ROW
            // NUMBER ALL TILES
            for (i = 1; i <= boardSize; i += 1) {
                full_array[i-1] = i + count;
            }
            // Create temporary array and add it to final board
            std::vector<int> temp_array = full_array;
            MiniGameScreen().currentBoard[y-1] = temp_array;
            count += boardSize; // MOVE ON TO NEXT ROW

        }
    }
}

int getValue(int row, int column) {
    // RETRIEVE A VALUE AT GIVEN COORDINATES

    int value = MiniGameScreen().currentBoard[row][column];
    return value;

}

MiniGameScreen getParent() {

    return MiniGameScreen().getParent();

}

enum Operation getOperation() {

    return Operation;

}

int getpathLength () {

    return pathLength;

}

MiniGameScreen move (int row, int column, MiniGameScreen::Operation op) {

    if (op == ) {

        if (column == 3) {
            //OUT OF BOUNDS
            return NULL;
        } else if (MiniGameScreen().currentBoard[row][column + 1] != 0) {
            // DESTINATION NOT EMPTY
            return NULL;
        } else {
            // GENERATE NEW MiniGameScreen AND UPDATE VARIABLES
            MiniGameScreen newState;



        }
    }

}
