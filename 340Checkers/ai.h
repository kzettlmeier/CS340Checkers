#ifndef AI_H
#define AI_H

#include "board.h"
#include <vector>

using namespace std;

class AI : public Board
{
public:
    AI();
    struct moves {
        const char *currentPosition;
        const char *newPositions[4];
    };
    vector<moves> availableMoves;
    //Method to check all moves for the computer
    void checkAllComputerMoves();
    //Convert integer to character
    char convertIntToChar(int num);
};

#endif // AI_H
