//
// Created by Arman Franco on 10/27/17.
//

#include "Screens/MiniGameScreen.hpp"
#include <vector>
#include <cmath>

int boardSize;

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

void MiniGameScreen::setToInitialState(int numberOfEmptySlots) {

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

int MiniGameScreen::getValue(int row, int column) {
    // RETRIEVE A VALUE AT GIVEN COORDINATES

    int value = MiniGameScreen().currentBoard[row][column];
    return value;

}

MiniGameScreen* MiniGameScreen::getParent() {

    return parentBoard;

}

MiniGameScreen::Operation MiniGameScreen::getOperation() {

    return boardOperation;

}

int MiniGameScreen::getPathLength () {

    return pathLength;

}

MiniGameScreen MiniGameScreen::move (int row, int column, MiniGameScreen::Operation op) {

    if (op == MiniGameScreen().MOVERIGHT) {

        if (column == 3) {
            //OUT OF BOUNDS
            return *this;
        } else if (MiniGameScreen().currentBoard[row][column + 1] != 0) {
            // DESTINATION NOT EMPTY
            return *this;
        } else {
            // GENERATE NEW MiniGameScreen AND UPDATE VARIABLES
            MiniGameScreen newState;
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
    } else if (op == MiniGameScreen().MOVELEFT) {
        if (column == 0) {
            // OUT OF BOUNDS
            return *this;
        } else if (currentBoard[row][column - 1] != 0) {
            // DESTINATION NOT EMPTY
            return *this;
        } else {

            // GENERATE NEW MiniGameScreen AND UPDATE VARIABLES
            MiniGameScreen newState;
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
    } else if (op == MiniGameScreen().MOVEDOWN){

        if (row == 3) {
            // OUT OF BOUNDS
            return *this;
        } else if (currentBoard[row + 1][column] != 0) {
            // DESITNATION NOT EMPTY
            return *this;
        } else {
            // Generate new PuzzleState and update variables
            MiniGameScreen newState;
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
    } else if (op == MiniGameScreen().MOVEUP) {

        if (row == 0) {
            // OUT OF BOUNDS
            return *this;
        } else if (currentBoard[row - 1][column] != 0) {
            // DESTINATION NOT EMPTY
            return *this;
        } else {
            // Create new PuzzleState and update variables
            MiniGameScreen newState;
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

MiniGameScreen MiniGameScreen::flip (int startRow, int startColumn, int endRow, int endColumn) {

// Generate puzzle state
    MiniGameScreen newState;
    int distance = std::abs(startRow-endRow) + std::abs(startColumn-endColumn);

    if (distance == 1) {
        if (startRow == endRow && startColumn < endColumn) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
            return newState;
        }else if (startRow == endRow && endColumn < startColumn) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
            return newState;
        } else if (startColumn == endColumn && startRow < endRow) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
            return newState;
        } else if (startColumn == endColumn && endRow < startRow) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
            return newState;
        }
        return *this;
    } else if (distance == 2) {

        if (startRow < endRow && startColumn < endColumn) {
            if (getValue(startRow, startColumn + 1) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
                return newState.flip(startRow, startColumn + 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
                return newState.flip(startRow + 1, startColumn, endRow, endColumn);
            }
        } else if (startRow > endRow && startColumn > endColumn) {
            if (getValue(startRow, startColumn - 1) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
                return newState.flip(startRow, startColumn - 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
                return newState.flip(startRow - 1, startColumn, endRow, endColumn);
            }
        } else if (startRow < endRow && startColumn > endColumn) {
            if (getValue(startRow, startColumn - 1) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
                return newState.flip(startRow, startColumn - 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
                return newState.flip(startRow + 1, startColumn, endRow, endColumn);
            }
        } else if (startRow > endRow && startColumn < endColumn) {
            if (getValue(startRow, startColumn + 1) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
                return newState.flip(startRow, startColumn + 1, endRow, endColumn);
            } else {
                newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
                return newState.flip(startRow - 1, startColumn, endRow, endColumn);
            }
        } else if (startRow == endRow && startColumn < endColumn) {
            if (getValue(startRow, startColumn + 1) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
                return newState.flip(startRow, startColumn + 1, endRow, endColumn);
            } else {
                return *this;
            }
        } else if (startRow == endRow && startColumn > endColumn) {
            if (getValue(startRow, startColumn - 1) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
                return newState.flip(startRow, startColumn - 1, endRow, endColumn);
            } else {
                return *this;
            }
        } else if (startRow < endRow && startColumn == endColumn) {
            if (getValue(startRow + 1, startColumn) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
                return newState.flip(startRow + 1, startColumn, endRow, endColumn);
            } else {
                return *this;
            }
        } else if (startRow > endRow && startColumn == endColumn) {
            if (getValue(startRow - 1, startColumn) == 0) {
                newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
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
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                }
            } else if (endRow > startRow) {
                if (getValue(startRow + 1, startColumn) == 0) {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                }
            } else {
                return *this;
            }
        } else if (std::abs(startColumn-endColumn) == 2 && startColumn > endColumn) {
            if (endRow < startRow) {
                if (getValue(startRow - 1, startColumn) == 0) {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                }
            } else if (endRow > startRow) {
                if (getValue(startRow + 1, startColumn) == 0) {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                }
            } else {
                return *this;
            }
        } else if (std::abs(startRow-endRow) == 2 && startRow < endRow) {
            if (startColumn > endColumn) {
                if (getValue(startRow, startColumn - 1) == 0) {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                }
            } else if (startColumn < endColumn) {
                if (getValue(startRow, startColumn + 1) == 0) {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
                    return newState.flip(startRow + 1, startColumn, endRow, endColumn);
                }
            }else {
                return *this;
            }
        } else if (std::abs(startRow-endRow) == 2 && startRow > endRow) {
            if (startColumn > endColumn) {
                if (getValue(startRow, startColumn - 1) == 0) {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
                    return newState.flip(startRow, startColumn - 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                }
            } else if (startColumn < endColumn) {
                if (getValue(startRow, startColumn + 1) == 0) {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
                    return newState.flip(startRow, startColumn + 1, endRow, endColumn);
                } else {
                    newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
                    return newState.flip(startRow - 1, startColumn, endRow, endColumn);
                }
            } else {
                return *this;
            }
        } else if (startRow - endRow == 3) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVEUP);
            return newState.flip(startRow - 1, startColumn, endRow, endColumn);
        } else if (startRow - endRow == -3) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVEDOWN);
            return newState.flip(startRow + 1, startColumn, endRow, endColumn);
        } else if (startColumn - endColumn == 3) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVELEFT);
            return newState.flip(startRow, startColumn - 1, endRow, endColumn);
        } else if (startColumn - endColumn == -3) {
            newState = move(startRow, startColumn, MiniGameScreen().MOVERIGHT);
            return newState.flip(startRow, startColumn + 1, endRow, endColumn);
        }
    } else {
        return *this;
    }
    return *this;

}

MiniGameScreen* MiniGameScreen::shuffleBoard(int pathLength) {

    int direction;
    int row = 0;
    int column = 0;

    for (int i = 0; i < currentBoard.size(); i++) {
        for (int x = 0; x < currentBoard.size(); x++) {
            if(currentBoard[i][x] == 0) {
                row = i;
                column = x;
            }
        }
    }

    // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT

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

    if (pathLength == 0) {
        return this;

    } else if (direction == 0 && getValue(row - 1, column) != 0) {

        //EMPTY SPACE MOVES UP
        MiniGameScreen newState;
        newState = move(row - 1, column, MiniGameScreen().MOVEDOWN);
        return newState.shuffleBoard(pathLength - 1);

    } else if (direction == 1 && getValue(row, column + 1) != 0) {

        //EMPTY SPACE MOVES RIGHT
        MiniGameScreen newState;
        newState = move(row, column + 1, MiniGameScreen().MOVELEFT);
        return newState.shuffleBoard(pathLength - 1);

    } else if (direction == 2 && getValue(row + 1, column) != 0) {

        //EMPTY SPACE MOVES DOWN
        MiniGameScreen newState;
        newState = move(row + 1, column, MiniGameScreen().MOVEUP);
        return newState.shuffleBoard(pathLength - 1);

    } else if (direction == 3 && getValue(row, column - 1) != 0) {

        //EMPTY SPACE MOVES LEFT
        MiniGameScreen newState;
        newState = move(row, column - 1, MiniGameScreen().MOVERIGHT);
        return newState.shuffleBoard(pathLength - 1);

    } else {
        return shuffleBoard(pathLength);
    }

}

bool MiniGameScreen::isEmpty(int row, int column) {

    // CHECK IF VALUE AT GIVEN TILE LOCATION IS EMPTY (i.e. is 0)

    int value = currentBoard[row][column];

    if (value == 0) {
        return true;
    } else {
        return false;
    }

}

MiniGameScreen* MiniGameScreen::getStateWithShortestPath() {

    // Trivial default implementation
    return this;
}

int MiniGameScreen::getRandom (int array[]) {

    // METHOD TO PULL RANDOM INTEGER FROM A GIVEN ARRAY
    int randIndex = rand() % sizeof(array);
    return array[randIndex];

};



