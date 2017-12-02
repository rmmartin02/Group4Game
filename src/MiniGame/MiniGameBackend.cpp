//
// Created by Arman Franco on 10/27/17.
//

#include "MiniGameBackend.hpp"
#include <vector>
#include <cmath>
#include <iostream>

int boardSize;

int pathLength;

MiniGameScreenBackend::MiniGameScreenBackend() {

    //MiniGameScreenBackend::Operation Operation;
    //int pathLength = 0;
    //MiniGameScreenBackend parentBoard;
    //std::vector<std::vector<int>> currentBoard;
    //int boardSize;

};

void MiniGameScreenBackend::setCurrentBoard (int size) {

    boardSize = size;

    std::vector<std::vector<int> > temp(size, std::vector<int>(size));

    currentBoard = temp;

    /**
    currentBoard.resize(size);

    for (int i = 0; i < size; ++ i) {
        currentBoard[i].resize(size);
    }
     **/

}

void MiniGameScreenBackend::setToInitialState(unsigned int numberOfEmptySlots) {

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
            currentBoard[y-1] = temp_array;
            count += boardSize;
        } else { // IF NOT FINAL ROW
            // NUMBER ALL TILES
            for (i = 1; i <= boardSize; i += 1) {
                full_array[i-1] = i + count;
            }
            // Create temporary array and add it to final board
            std::vector<int> temp_array = full_array;
            currentBoard[y-1] = temp_array;
            count += boardSize; // MOVE ON TO NEXT ROW

        }
    }
}

int MiniGameScreenBackend::getValue(int row, int column) {
    // RETRIEVE A VALUE AT GIVEN COORDINATES

    int value = currentBoard[row][column];
    return value;

}

MiniGameScreenBackend* MiniGameScreenBackend::getParent() {

    return parentBoard;

}

MiniGameScreenBackend::Operation MiniGameScreenBackend::getOperation() {

    return boardOperation;

}

int MiniGameScreenBackend::getPathLength () {

    return pathLength;

}

MiniGameScreenBackend MiniGameScreenBackend::move (int row, int column, MiniGameScreenBackend::Operation op) {

    if (op == MOVERIGHT) {

        if (column == 3) {
            //OUT OF BOUNDS
            return *this;
        } else if (currentBoard[row][column + 1] != 0) {
            // DESTINATION NOT EMPTY
            return *this;
        } else {
            // GENERATE NEW MiniGameScreenBackend AND UPDATE VARIABLES
            MiniGameScreenBackend newState;
            newState.boardOperation = op;
            newState.parentBoard = this;
            newState.pathLength = pathLength + 1;

            // REFRESH NEW BOARD
            newState.currentBoard = currentBoard; // CHECK EFFICACY
            int value = newState.currentBoard[row][column];
            newState.currentBoard[row][column] = 0;
            newState.currentBoard[row][column + 1] = value;

            return newState;
        }
    } else if (op == MOVELEFT) {
        if (column == 0) {
            // OUT OF BOUNDS
            return *this;
        } else if (currentBoard[row][column - 1] != 0) {
            // DESTINATION NOT EMPTY
            return *this;
        } else {

            // GENERATE NEW MiniGameScreenBackend AND UPDATE VARIABLES
            MiniGameScreenBackend newState;
            newState.boardOperation = op;
            newState.parentBoard = this;
            newState.pathLength = pathLength + 1;

            // REFRESH NEW BOARD
            newState.currentBoard = currentBoard;
            int value = newState.currentBoard[row][column];
            newState.currentBoard[row][column] = 0;
            newState.currentBoard[row][column - 1] = value;

            return newState;
        }
    } else if (op == MOVEDOWN){

        if (row == 3) {
            // OUT OF BOUNDS
            return *this;
        } else if (currentBoard[row + 1][column] != 0) {
            // DESITNATION NOT EMPTY
            return *this;
        } else {
            // Generate new PuzzleState and update variables
            MiniGameScreenBackend newState;
            newState.boardOperation = op;
            newState.parentBoard = this;
            newState.pathLength = pathLength + 1;

            // Update new board
            newState.currentBoard = currentBoard;
            int value = newState.currentBoard[row][column];
            newState.currentBoard[row][column] = 0;
            newState.currentBoard[row + 1][column] = value;

            return newState;
        }
    } else if (op == MOVEUP) {

        if (row == 0) {
            // OUT OF BOUNDS
            return *this;
        } else if (currentBoard[row - 1][column] != 0) {
            // DESTINATION NOT EMPTY
            return *this;
        } else {
            // Create new PuzzleState and update variables
            MiniGameScreenBackend newState;
            newState.boardOperation = op;
            newState.parentBoard = this;
            newState.pathLength = pathLength + 1;

            // Update new board
            newState.currentBoard = currentBoard;
            int value = newState.currentBoard[row][column];
            newState.currentBoard[row][column] = 0;
            newState.currentBoard[row - 1][column] = value;

            return newState;

        }

    } else {
        // Any other case
        return *this;
    }
}

MiniGameScreenBackend MiniGameScreenBackend::flip (int startRow, int startColumn, int endRow, int endColumn) {

// Generate puzzle state
    MiniGameScreenBackend newState;
    int distance = std::abs(startRow-endRow) + std::abs(startColumn-endColumn);

    if (distance == 1) {
        if (startRow == endRow && startColumn < endColumn) {
            newState = move(startRow, startColumn, MOVERIGHT);
            return newState;
        }else if (startRow == endRow && endColumn < startColumn) {
            newState = move(startRow, startColumn, MOVELEFT);
            return newState;
        } else if (startColumn == endColumn && startRow < endRow) {
            newState = move(startRow, startColumn, MOVEDOWN);
            return newState;
        } else if (startColumn == endColumn && endRow < startRow) {
            newState = move(startRow, startColumn, MOVEUP);
            return newState;
        }
        return *this;
    } else if (distance == 2) {

        if (startRow < endRow && startColumn < endColumn) {
            if (getValue(startRow, startColumn + 1) == 0) {
                newState = move(startRow, startColumn, MOVERIGHT);
                return newState.flip(startRow, startColumn + 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MOVEDOWN);
                return newState.flip(startRow + 1, startColumn, endRow, endColumn);
            }
        } else if (startRow > endRow && startColumn > endColumn) {
            if (getValue(startRow, startColumn - 1) == 0) {
                newState = move(startRow, startColumn, MOVELEFT);
                return newState.flip(startRow, startColumn - 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MOVEUP);
                return newState.flip(startRow - 1, startColumn, endRow, endColumn);
            }
        } else if (startRow < endRow && startColumn > endColumn) {
            if (getValue(startRow, startColumn - 1) == 0) {
                newState = move(startRow, startColumn, MOVELEFT);
                return newState.flip(startRow, startColumn - 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MOVEDOWN);
                return newState.flip(startRow + 1, startColumn, endRow, endColumn);
            }
        } else if (startRow > endRow && startColumn < endColumn) {
            if (getValue(startRow, startColumn + 1) == 0) {
                newState = move(startRow, startColumn, MOVERIGHT);
                return newState.flip(startRow, startColumn + 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MOVEUP);
                return newState.flip(startRow - 1, startColumn, endRow, endColumn);
            }
        } else if (startRow == endRow && startColumn < endColumn) {
            if (getValue(startRow, startColumn + 1) == 0) {
                newState = move(startRow, startColumn, MOVERIGHT);
                return newState.flip(startRow, startColumn + 1, endRow, endColumn);
            } else {
                return *this;
            }
        } else if (startRow == endRow && startColumn > endColumn) {
            if (getValue(startRow, startColumn - 1) == 0) {
                newState = move(startRow, startColumn, MOVELEFT);
                return newState.flip(startRow, startColumn - 1, endRow, endColumn);
            } else {
                return *this;
            }
        } else if (startRow < endRow && startColumn == endColumn) {
            if (getValue(startRow + 1, startColumn) == 0) {
                newState = move(startRow, startColumn, MOVEDOWN);
                return newState.flip(startRow + 1, startColumn, endRow, endColumn);
            } else {
                return *this;
            }
        } else if (startRow > endRow && startColumn == endColumn) {
            if (getValue(startRow - 1, startColumn) == 0) {
                newState = move(startRow, startColumn, MOVEUP);
                return newState.flip(startRow - 1, startColumn, endRow, endColumn);
            } else {
                return *this;
            }
        } else {
            return *this;
        }

    } else if (distance == 3) {

        if (std::abs(startColumn-endColumn) == 2 && startColumn < endColumn) {
            if (endRow < startRow) {
                if (getValue(startRow - 1, startColumn) == 0) {
                    newState = move(startRow, startColumn, MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                }
            } else if (endRow > startRow) {
                if (getValue(startRow + 1, startColumn) == 0) {
                    newState = move(startRow, startColumn, MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                }
            } else {
                return *this;
            }
        } else if (std::abs(startColumn-endColumn) == 2 && startColumn > endColumn) {
            if (endRow < startRow) {
                if (getValue(startRow - 1, startColumn) == 0) {
                    newState = move(startRow, startColumn, MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                }
            } else if (endRow > startRow) {
                if (getValue(startRow + 1, startColumn) == 0) {
                    newState = move(startRow, startColumn, MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                }
            } else {
                return *this;
            }
        } else if (std::abs(startRow-endRow) == 2 && startRow < endRow) {
            if (startColumn > endColumn) {
                if (getValue(startRow, startColumn - 1) == 0) {
                    newState = move(startRow, startColumn, MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                }
            } else if (startColumn < endColumn) {
                if (getValue(startRow, startColumn + 1) == 0) {
                    newState = move(startRow, startColumn, MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                }
            }else {
                return *this;
            }
        } else if (std::abs(startRow-endRow) == 2 && startRow > endRow) {
            if (startColumn > endColumn) {
                if (getValue(startRow, startColumn - 1) == 0) {
                    newState = move(startRow, startColumn, MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                }
            } else if (startColumn < endColumn) {
                if (getValue(startRow, startColumn + 1) == 0) {
                    newState = move(startRow, startColumn, MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                }
            } else {
                return *this;
            }
        } else if (startRow - endRow == 3) {
            newState = move(startRow, startColumn, MOVEUP);
            return newState.flip(startRow - 1, startColumn, endRow, endColumn);
        } else if (startRow - endRow == -3) {
            newState = move(startRow, startColumn, MOVEDOWN);
            return newState.flip(startRow + 1, startColumn, endRow, endColumn);
        } else if (startColumn - endColumn == 3) {
            newState = move(startRow, startColumn, MOVELEFT);
            return newState.flip(startRow, startColumn - 1, endRow, endColumn);
        } else if (startColumn - endColumn == -3) {
            newState = move(startRow, startColumn, MOVERIGHT);
            return newState.flip(startRow, startColumn + 1, endRow, endColumn);
        }
    } else {
        return *this;
    }
    return *this;

}

MiniGameScreenBackend MiniGameScreenBackend::shuffleBoard(int pathLength) {

    int direction;
    int row = 0;
    int column = 0;

    // LOCATE ZERO
    for (int i = 0; i < currentBoard.size(); i++) {
        for (int x = 0; x < currentBoard.size(); x++) {
            if(currentBoard[i][x] == 0) {
                row = i;
                column = x;
            }
        }
    }

    //std::cout << "board size is" << boardSize << std::endl;

    // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT

    if (boardSize == 3){

        if (column == 3 && row == 3) {

            int array [] = {0, 3}; //CORNER CASE: Excludes RIGHT & DOWN
            direction = getRandom(array);

        } else if (column == 0 && row == 0) {

            int array [] = {1, 2}; //CORNER CASE: Excludes LEFT & UP
            direction = getRandom(array);

        } else if (column == 3 && row == 0) {

            int array [] = {2, 3}; //CORNER CASE: Excludes RIGHT & UP
            direction = getRandom(array);

        } else if (column == 0 && row == 3) {

            int array [] = {0, 1}; //CORNER CASE: Excludes LEFT & DOWN
            direction = getRandom(array);

        } else if (column == 3) {

            int array [] = {0, 2, 3};
            direction = getRandom(array); //EXCLUDES RIGHT

        } else if (row == 3) {

            int array [] = {0, 1, 3}; // EXCLUDES DOWN
            direction = getRandom(array);

        } else if (column == 0) {

            int array [] = {0, 1, 2}; //EXCLUDES LEFT
            direction = getRandom(array);

        } else if (row == 0) {

            int array [] = {1, 2, 3}; //EXCLUDES UP
            direction = getRandom(array);

        } else {

            int array [] = {0, 1, 2, 3}; // NO EXCLUSIONS
            direction = getRandom(array);

        }

    } else if (boardSize == 2) {

        if (column == 1 && row == 1) {

            int array [] = {0, 3}; //CORNER CASE: Excludes RIGHT & DOWN
            direction = getRandom(array);
            //std::cout << "col 1 row 1 direction is" << direction <<std::endl;

        } else if (column == 0 && row == 0) {

            int array [] = {1, 2}; //CORNER CASE: Excludes LEFT & UP
            direction = getRandom(array);

        } else if (column == 1 && row == 0) {

            int array [] = {2, 3}; //CORNER CASE: Excludes RIGHT & UP
            direction = getRandom(array);

        } else if (column == 0 && row == 1) {

            int array [] = {0, 1}; //CORNER CASE: Excludes LEFT & DOWN
            direction = getRandom(array);

        } else if (column == 1) {

            int array [] = {0, 2, 3};
            direction = getRandom(array); //EXCLUDES RIGHT

        } else if (row == 1) {

            int array [] = {0, 1, 3}; // EXCLUDES DOWN
            direction = getRandom(array);

        } else if (column == 0) {

            int array [] = {0, 1, 2}; //EXCLUDES LEFT
            direction = getRandom(array);

        } else if (row == 0) {

            int array [] = {1, 2, 3}; //EXCLUDES UP
            direction = getRandom(array);

        } else {

            int array [] = {0, 1, 2, 3}; // NO EXCLUSIONS
            direction = getRandom(array);

        }

    } else
        direction = 0; //remove later

    //std::cout << direction <<std::endl;

    if (pathLength == 0) {
        //std::cout << "return this" << std::endl;
        return *this;

    } else if (direction == 0 && this->getValue(row - 1, column) != 0) {

        //EMPTY SPACE MOVES UP
        MiniGameScreenBackend newState;
        newState = move(row - 1, column, MOVEDOWN);
        return newState.shuffleBoard(pathLength - 1);

    } else if (direction == 1 && this->getValue(row, column + 1) != 0) {

        //EMPTY SPACE MOVES RIGHT
        MiniGameScreenBackend newState;
        newState = move(row, column + 1, MOVELEFT);
        return newState.shuffleBoard(pathLength - 1);

    } else if (direction == 2 && this->getValue(row + 1, column) != 0) {

        //EMPTY SPACE MOVES DOWN
        MiniGameScreenBackend newState;
        newState = move(row + 1, column, MOVEUP);
        return newState.shuffleBoard(pathLength - 1);

    } else if (direction == 3 && this->getValue(row, column - 1) != 0) {

        //EMPTY SPACE MOVES LEFT
        MiniGameScreenBackend newState;
        newState = move(row, column - 1, MOVERIGHT);
        return newState.shuffleBoard(pathLength - 1);

    } else {
        return shuffleBoard(pathLength);
    }

}

bool MiniGameScreenBackend::isEmpty(int row, int column) {

    // CHECK IF VALUE AT GIVEN TILE LOCATION IS EMPTY (i.e. is 0)

    int value = currentBoard[row][column];

    if (value == 0) {
        return true;
    } else {
        return false;
    }

}

MiniGameScreenBackend* MiniGameScreenBackend::getStateWithShortestPath() {

    // Trivial default implementation
    return this;
}

int MiniGameScreenBackend::getRandom (int array[]) {

    // METHOD TO PULL RANDOM INTEGER FROM A GIVEN ARRAY
    int randIndex = rand() % sizeof(array);

    //std::cout << "Rand no is" << array[randIndex] <<std::endl;

    return array[randIndex];

};



