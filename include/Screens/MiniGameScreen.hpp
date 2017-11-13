//
// Created by Arman Franco on 10/27/17.
// Refactored from [INSERT]
//

#ifndef MINIGAMESCREEN_HPP
#define MINIGAMESCREEN_HPP

#include <vector>


class MiniGameScreen{

public:

    std::vector<std::vector<int>> currentBoard;

    int boardSize;

    MiniGameScreen();

    // NEW

    std::vector<std::vector<int>> setCurrentBoard (int size);


    // INHERITED
    enum class Operation {MOVERIGHT, MOVELEFT, MOVEUP, MOVEDOWN};

    void setToInitialState(int numberOfEmptySlots);

    int getValue(int row, int column);

    MiniGameScreen getParent();

    Operation getOperation();

    int getPathLength();

    MiniGameScreen move(int row, int column, Operation op);

    MiniGameScreen flip(int startRow, int startColumn, int endRow, int endColumn);

    MiniGameScreen shuffleBoard(int pathLength);

    bool isEmpty(int row, int column);

    MiniGameScreen getStateWithShortestPath();


};


#endif //MINIGAMESCREEN_HPP
