/*
 * This is the game header file.
 * This is where the current pieces are stored
 *  as well as the player scores.
 * We have all the methods needed for game logic stored here as well.
 */
#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game : public Board
{
public:
    int currentPiece;
    int currentKingPiece;
    int player1Score;
    int player2Score;
    bool anotherJump;
    Game();
    bool makeAMove(int player, char *pieceToMove, char *moveTo);
    int convertCharDimensionToInt(char secondDimension);
    bool moveRegularP1Up(int newFirstDimension, int currentFirstDimension, int newSecondDimension,
                          int currentSecondDimension);
    bool moveKingP1(int newFirstDimension, int currentFirstDimension, int newSecondDimension,
                    int currentSecondDimension);
    bool moveRegularP2Down(int newFirstDimension, int currentFirstDimension, int newSecondDimension,
                           int currentSecondDimension);
    bool moveKingP2(int newFirstDimension, int currentFirstDimension, int newSecondDimension,
                    int currentSecondDimension);
    bool canJumpPlayer(char *currentPos);
};

#endif // GAME_H
