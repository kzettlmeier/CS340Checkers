#ifndef AI_H
#define AI_H

#include "game.h"
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

class AI : public Game
{
public:
    AI();
    struct moves {
        const char *currentPosition;
        const char *newPositions[4];
        const char *jumps[4];
    };
    vector<moves> availableMoves;
    //Method to check all moves for the computer
    void checkAllComputerMoves();
    //Convert integer to character
    char convertIntToChar(int num);
    //Decide which move to take
    string decider();
    //Remove data from availableMoves
    void removeData();
};

#endif // AI_H
