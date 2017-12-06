//
// Created by Arman Franco on 10/27/17.
// Refactored from [INSERT]
//

#ifndef MINIGAMESCREENBACKEND_HPP
#define MINIGAMESCREENBACKEND_HPP

#include <vector>



class MiniGameScreenBackend{

public:

    std::vector<std::vector<int>> currentBoard;

    int boardSize;

    int pathLength;


    int randIndex;

    MiniGameScreenBackend* parentBoard;

    MiniGameScreenBackend();

    // NEW

    void setCurrentBoard (int size);


    // INHERITED

    enum Operation {MOVERIGHT, MOVELEFT, MOVEUP, MOVEDOWN};

    Operation boardOperation;

    void setToInitialState(unsigned int numberOfEmptySlots);

    int getValue(int row, int column);

    MiniGameScreenBackend* getParent();

    Operation getOperation();

    int getPathLength();

    MiniGameScreenBackend move(int row, int column, Operation op);

    MiniGameScreenBackend flip(int startRow, int startColumn, int endRow, int endColumn);

    MiniGameScreenBackend shuffleBoard(int pathLength);

    bool isEmpty(int row, int column);

    MiniGameScreenBackend* getStateWithShortestPath();


    int getRandom(int array[]);

};


#endif //MINIGAMESCREENBACKEND_HPP
