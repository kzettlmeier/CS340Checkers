/**
 *
 *  \file ai.h
 *  A header file that contains the objects for the ai.cpp file
 *
 *  This contains the methods that the AI runs when checking the moves and creating its moves.
 *  It also contains the structure for the types of moves, such as: the current position, a new possible position, and the number of possible jumps.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 */

/**
 *  \typedef indef AI_H
 *  \def define AI_H
 */
#ifndef AI_H
#define AI_H

#include "game.h"
#include <vector>
#include <string.h>
#include <iostream>

/**
 *  \namespace std
 *      uses the standard namespace for simplicity of implementation
 */
using namespace std;

/**
 * @brief The AI class
 */
class AI : public Game
{
public:
    AI();
    /**
     * @brief The moves struct
     *  \struct moves
     *      contains the constant character values of the currentPosition, the newPositions, and the number of jumps
     *
     *  \var *currentPosition the current position
     *  \var *newPositions[4] the possible new positions for a given piece
     *  \var *jumps[4] the number of jumps that a piece can do
     */
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
