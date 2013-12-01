/**
 *  \file game.h
 *  The game header file
 *
 *  This is the place where all of the current pieces from the game board are stored; it also
 *  includes the scores of eacher player, which indicates how many pieces a player has left on
 *  the board. All of the methods that are required for the game logic are stored in this file
 *  as well. It makes it much easier to maintain the information for the games moves here rather
 *  than keeping the information with the computational parts of the application.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *  \bug No bugs have been spotted.
 *
 *  \typedef GAME_H an include guard
 *  \def GAME_H defines the game logic
 *  \namespace std using namespace identifier
 */

/*
 * This is the game header file.
 * This is where the current pieces are stored
 *  as well as the player scores.
 * We have all the methods needed for game logic stored here as well.
 */
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <string.h>
#include <iostream>

using namespace std;
/**
 * @brief The Game class
 *  The game class inherits the Board class
 *
 *  \var currentPiece the current selected regular piece
 *  \var currentKingPiece the current King piece selected
 *  \var player1Score player 1's current pieces left
 *  \var player2Score player 2's current pieces left
 *  \var anotherJump a boolean to check if another jump can be made
 *  \fn Game()
 *  \brief A member function
 *  \fn makeAmove
 *  \brief checks if a move can be made with a given piece
 *  \param player player turn
 *  \param pieceToMove the coordinate of a selected piece
 *  \param location of destination
 *  \return a function call to a specific move for a specific piece
 *  \fn convertCharDimensionToInt
 *  \brief converts the Character Dimension to an Integer
 *  \param secondDimension the coordinate of a piece
 *  \return an integer that corresponds to the move
 *  \fn moveRegularP1Up
 *  \brief moves a regular player 1 piece
 *  \param newFirstDimension new part of coordinate
 *  \param currentFirstDimension current half of coordinate
 *  \param newSecondDimension new second part of new coordinate
 *  \param currentSecondDimension current second half of coordinate
 *  \return successful piece movement
 *  \fn moveKingP1
 *  \brief moves a player 1 King piece
 *  \param newFirstDimension new part of coordinate
 *  \param currentFirstDimension current half of coordinate
 *  \param newSecondDimension new second part of new coordinate
 *  \param currentSecondDimension current second half of coordinate
 *  \return successful piece movement
 *  \fn moveRegularP2Down
 *  \brief moves a regular player 2 piece
 *  \param newFirstDimension new part of coordinate
 *  \param currentFirstDimension current half of coordinate
 *  \param newSecondDimension new second part of new coordinate
 *  \param currentSecondDimension current second half of coordinate
 *  \return successful piece movement
 *  \fn moveKingP2
 *  \brief moves a player 2 King piece
 *  \param newFirstDimension new part of coordinate
 *  \param currentFirstDimension current half of coordinate
 *  \param newSecondDimension new second part of new coordinate
 *  \param currentSecondDimension current second half of coordinate
 *  \return successful piece movement
 *  \fn canJumpPlayer
 *  \brief checks to see if a piece can make a jump
 *  \param currentPos the current position of the current piece
 *  \return successful jump of a piece
 *  \fn jumpPos
 *  \brief jumps the piece and updates the coordinates of the current piece
 *  \param currentPos the current position of the current piece
 *  \return new coordinates of the current game piece
 *  \fn convertIntToChar
 *  \brief converts the int that was returned in convertCharDimensionToInt back to a character
 *  \param num an integer
 *  \return a character corresponding to the board
 *
 */
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
    string jumpPos(char *currentPos);
    char convertIntToChar(int num);
};

#endif // GAME_H
