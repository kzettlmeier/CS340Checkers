/**
 *  \file game.cpp
 *  \brief Game Logic implementation
 *
 *  All game logic is coded here. It contains the information for keeping track
 *  of moves for both players, whether or not a player is the CPU or not.
 *  It receives information of where a player wants to commit their move and properly
 *  insepcts their commitment to see if a given move attempt is legal.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *
 *  \namespace std using namespace identifier
 */

/*
 * All game logic is coded here.
 * PLEASE NOTE:
 * IN THIS CODE THE ONLY WAY TO DO ANY JUMP MORE THAN 1 OPPONENT PIECE
 * YOU MUST JUMP 1 PIECE IN WHICH AFTER THAT JUMP THE PROGRAM CHECKS TO
 * SEE IF THERE IS ANOTHER POSSIBLE JUMP IN WHICH THE PROGRAM WILL ALLOW
 * YOU TO DO ANOTHER JUMP, THIS KEEPS GOING UNTIL THERE ARE NO MORE JUMPS
 * POSSIBLE
 */

#include "game.h"
#include <iostream>
#include <sstream>

using namespace std;

/**
 * @brief Game::Game
 *  The player scores are initially set to 12, since it's the number of pieces that each player
 *  has at maximum when the game starts
 *
 * \var player1Score the remaining pieces of player1
 * \var player2Score the remaining pieces of player2
 * \var anotherJump a boolean variable set to false intially since there's no piece to jump
 */
Game::Game()
{
    //Initialize the player scores
    player1Score = 12;
    player2Score = 12;
    //Set another jump to false because game has started and no
    //move has been made
    anotherJump = false;
}

//Method to make a move
/**
 * @brief Game::makeAMove
 *  Checks to see if a move is Valid
 *
 *  This method will scan the locations around a given selected piece on the board
 *  and will determine whether a piece can move to the desired location, which is also given by
 *  the player. The application will check to see if the move is valid. If the move is valid (which the type
 *  of moves are separated by regular player 1/2 moves and King player 1/2 pieces) then the values are
 *  sent as parameters to the method that takes care of the move for a given piece.
 *
 *
 * @param player player 1 or player 2
 * @param pieceToMove The selected piece's position
 * @param moveTo The desired destination of the selected piece
 * @return
 *
 *  \var currentPiece either 'o/x' for regular piece on command line
 *  \var currentKingPiece either 'O/X' for King Piece on command line
 */
bool Game::makeAMove(int player, char *pieceToMove, char *moveTo)
{
    //Check if the player is player 1 or player 2
    if (player == 1)
    {
        currentPiece = 'o';
        currentKingPiece = 'O';
    }
    else
    {
        currentPiece = 'x';
        currentKingPiece = 'X';
    }

    //Check if pieceToMove is the current players piece
    //First get the current position and position to move to into two integers
    int currentFirstDimension = pieceToMove[0] - '0';
    int currentSecondDimension;
    int newFirstDimension = moveTo[0] - '0';
    int newSecondDimension;

    //Change the current piece second dimension character to an integer
    currentSecondDimension = convertCharDimensionToInt(pieceToMove[1]);
    if (currentSecondDimension == -1)
    {
        cout << "There was an error converting the second dimension in the current position to an integer" << endl;
        return false;
    }

    //Change the new position second dimension from a character to an int
    newSecondDimension = convertCharDimensionToInt(moveTo[1]);
    if (newSecondDimension == -1)
    {
        cout << "There was an error converting the second dimension in the new position to an integer" << endl;
        return false;
    }

    //Make sure the dimensions are in bounds
    if (newFirstDimension > 7 || newFirstDimension < 0 || newSecondDimension > 7 || newSecondDimension < 0)
    {
        cout << "You tried to move to a position that was not on the board" << endl;
        return false;
    }

    //Check if the board piece chosen to move is the correct players to move
    if (board[currentFirstDimension][currentSecondDimension] == '#' || (board[currentFirstDimension][currentSecondDimension] != currentPiece &&
            board[currentFirstDimension][currentSecondDimension] != currentKingPiece))
    {
        cout << "You tried to choose a piece that was not your's" << endl;
        return false;
    }

    char currentPieceToMove = board[currentFirstDimension][currentSecondDimension];

    //We now know that the piece to move is the current players piece
    //Now check if the place to move is already filled
    if (board[newFirstDimension][newSecondDimension] != ' ')
    {
        cout << "You tried to move to a position that is already filled" << endl;
        return false;
    }

    //Check if the place to move is a possible move for the player
    //First check for regular piece if player 1
    if (currentPieceToMove == currentPiece && currentPiece == 'o')
    {
        return moveRegularP1Up(newFirstDimension, currentFirstDimension, newSecondDimension, currentSecondDimension);
    }
    //Check for king piece if player 1
    else if (currentPieceToMove == currentKingPiece && currentKingPiece == 'O')
    {
        return moveKingP1(newFirstDimension, currentFirstDimension, newSecondDimension, currentSecondDimension);
    }
    //Check for regular piece if player 2
    else if (currentPieceToMove == currentPiece && currentPiece == 'x')
    {
        return moveRegularP2Down(newFirstDimension, currentFirstDimension, newSecondDimension, currentSecondDimension);
    }
    //Check for king piece if player 2
    else if (currentPieceToMove == currentKingPiece && currentKingPiece == 'X')
    {
        return moveKingP2(newFirstDimension, currentFirstDimension, newSecondDimension, currentSecondDimension);
    }
    //Else there was an error and return false
    else
    {
        cout << "SHOULD NEVER GET HERE" << endl;
        return false;
    }
}

//Method to move a king player 1 piece
/**
 * @brief Game::moveKingP1
 *  Moves the player 1 King piece
 *
 *  This method is called upon the moveAMove method. What happens is that the game
 *  runs a series of error checks (is it inbounds, is the move legal, is the move not filled)
 *  and it runs a test to see if when making a move, a jump(s) is possible. If the move is a blank spot,
 *  then the method returns the move itself. If the game detects that a jump is possible, it will call up
 *  the method to make a jump and force the player to make the jump (as dictated by our game's logic).
 *  After the jump is made, then the game will test to see if another jump is possible, which if there results
 *  that another jump can be made then the game will force the player to jump once more. We felt that in our
 *  design, we had to make the game jump the player by force, or else a more difficult algorithm had to be
 *  implemented, which easily increases the difficulty of implementation exponentially.
 *
 * @param newFirstDimension
 * @param currentFirstDimension
 * @param newSecondDimension
 * @param currentSecondDimension
 * @return returns the valid move and moves the piece.
 */
bool Game::moveKingP1(int newFirstDimension, int currentFirstDimension, int newSecondDimension, int currentSecondDimension)
{
    //Check if the new dimensions are out of range of a move
    if (newFirstDimension > currentFirstDimension + 2 || newSecondDimension < currentSecondDimension - 2 ||
            newSecondDimension > currentSecondDimension + 2)
    {
        cout << "That is not a valid move" << endl;
        return false;
    }
    //Check if the move is [currentFirstDimension-1][currentSecondDimension-1] and anotherJump is false
    else if (currentFirstDimension - 1 == newFirstDimension && currentSecondDimension - 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //Check if the move is [currentFirstDimension-1][currentSecondDimension+1] and anotherJump is false
    else if (currentFirstDimension - 1 == newFirstDimension && currentSecondDimension + 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension-2][currentSecondDimension-2]
    else if ((board[currentFirstDimension-1][currentSecondDimension-1] == 'x' ||
             board[currentFirstDimension-1][currentSecondDimension-1] == 'X') &&
             currentFirstDimension - 2 == newFirstDimension && currentSecondDimension - 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension-1][currentSecondDimension-1] = ' ';
        //Decrement player 2 score
        player2Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension-2][currentSecondDimension+2]
    else if ((board[currentFirstDimension-1][currentSecondDimension+1] == 'x' ||
              board[currentFirstDimension-1][currentSecondDimension+1] == 'X') &&
             currentFirstDimension - 2 == newFirstDimension && currentSecondDimension + 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension-1][currentSecondDimension+1] = ' ';
        //Decrement player 2 score
        player2Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //Check if the move is [currentFirstDimension+1][currentSecondDimension-1] and anotherJump is false
    else if (currentFirstDimension + 1 == newFirstDimension && currentSecondDimension - 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //Check if the move is [currentFirstDimension+1][currentSecondDimension+1]
    else if (currentFirstDimension + 1 == newFirstDimension && currentSecondDimension + 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension+2][currentSecondDimension-2]
    else if ((board[currentFirstDimension+1][currentSecondDimension-1] == 'x' ||
             board[currentFirstDimension+1][currentSecondDimension-1] == 'X') &&
             currentFirstDimension + 2 == newFirstDimension && currentSecondDimension - 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension+1][currentSecondDimension-1] = ' ';
        //Decrement player 1 score
        player2Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension+2][currentSecondDimension+2]
    else if ((board[currentFirstDimension+1][currentSecondDimension+1] == 'x' ||
              board[currentFirstDimension+1][currentSecondDimension+1] == 'X') &&
             currentFirstDimension + 2 == newFirstDimension && currentSecondDimension + 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension+1][currentSecondDimension+1] = ' ';
        //Decrement player 1 score
        player2Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'O';
        return true;
    }
    //If anotherJump is possible then it had to have made a jump
    else if (anotherJump == true)
    {
        cout << "That move was not a jump" << endl;
        return false;
    }
    //Else the move is an invalid move
    else
    {
        cout << "The move requested was an invalid move" << endl;
        return false;
    }
    return false;
}

//Method to move a regular player 2 piece down the board
/**
 * @brief Game::moveRegularP2Down
 *  A method that moves a player 2's regular piece down the board
 *
 *  Similar to the moveKingP1 method, this is also called by the makeAMove method that
 *  verifies and validates the move with the given parameters from the makeAMove method. It
 *  checks to see if the move is valid (the destination spot is vacant, the move is within bounds
 *  of the board and is within bounds of a single empty move space). It also checks to see if a jump
 *  can be made, where if it can make a move, then the method calls forth another method to handle
 *  the jump; also, it keeps track to see if it can jump again after it had previously jumped a piece.
 *
 * @param newFirstDimension
 * @param currentFirstDimension
 * @param newSecondDimension
 * @param currentSecondDimension
 * @return true if a vaild move for the player2 regular piece, otherwise it will return false
 */
bool Game::moveRegularP2Down(int newFirstDimension, int currentFirstDimension, int newSecondDimension, int currentSecondDimension)
{
    //Check if the new dimensions are out of range of a move
    if (newFirstDimension > currentFirstDimension + 2 || newSecondDimension < currentSecondDimension - 2 ||
            newSecondDimension > currentSecondDimension + 2)
    {
        cout << "That is not a valid move" << endl;
        return false;
    }
    //Check if the move is [currentFirstDimension+1][currentSecondDimension-1] and anotherJump is false
    else if (currentFirstDimension + 1 == newFirstDimension && currentSecondDimension - 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 7)
        {
            board[newFirstDimension][newSecondDimension] = 'X';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'x';
        }
        return true;
    }
    //Check if the move is [currentFirstDimension+1][currentSecondDimension+1] and anotherJump is false
    else if (currentFirstDimension + 1 == newFirstDimension && currentSecondDimension + 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 7)
        {
            board[newFirstDimension][newSecondDimension] = 'X';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'x';
        }
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension+2][currentSecondDimension-2]
    else if ((board[currentFirstDimension+1][currentSecondDimension-1] == 'o' ||
             board[currentFirstDimension+1][currentSecondDimension-1] == 'O') &&
             currentFirstDimension + 2 == newFirstDimension && currentSecondDimension - 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension+1][currentSecondDimension-1] = ' ';
        //Decrement player 1 score
        player1Score--;
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 7)
        {
            board[newFirstDimension][newSecondDimension] = 'X';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'x';
        }
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension+2][currentSecondDimension+2]
    else if ((board[currentFirstDimension+1][currentSecondDimension+1] == 'o' ||
              board[currentFirstDimension+1][currentSecondDimension+1] == 'O') &&
             currentFirstDimension + 2 == newFirstDimension && currentSecondDimension + 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension+1][currentSecondDimension+1] = ' ';
        //Decrement player 1 score
        player1Score--;
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 7)
        {
            board[newFirstDimension][newSecondDimension] = 'X';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'x';
        }
        return true;
    }
    //If anotherJump is true then it must have made another jump
    else if (anotherJump == true)
    {
        cout << "That move was not a jump" << endl;
        return false;
    }
    //Else the move is an invalid move
    else
    {
        cout << "The move requested was an invalid move" << endl;
        return false;
    }
    return false;
}

//Method to move a king player 2 piece
/**
 * @brief Game::moveKingP2
 *  Moves the player 2's King piece
 *
 *  Please see the detailed information about the player moveKingP1 method, as their
 *  functions are practically the same. The main difference being in that our game Logic
 *  dictates that player 1 pieces move "up" generally and the player 1 King initially moves
 *  down; whereas, the player 2 pieces move "down" the board and the player 2 King pieces move
 *  up.
 *
 * @param newFirstDimension
 * @param currentFirstDimension
 * @param newSecondDimension
 * @param currentSecondDimension
 * @return true if the move attempt passes the error checks and is valid.
 */
bool Game::moveKingP2(int newFirstDimension, int currentFirstDimension, int newSecondDimension, int currentSecondDimension)
{
    //Check if the new dimensions are out of range of a move
    if (newFirstDimension > currentFirstDimension + 2 || newSecondDimension < currentSecondDimension - 2 ||
            newSecondDimension > currentSecondDimension + 2)
    {
        cout << "That is not a valid move" << endl;
        return false;
    }
    //Check if the move is [currentFirstDimension+1][currentSecondDimension-1] and anotherJump is false
    else if (currentFirstDimension + 1 == newFirstDimension && currentSecondDimension - 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //Check if the move is [currentFirstDimension+1][currentSecondDimension+1] and anotherJump is false
    else if (currentFirstDimension + 1 == newFirstDimension && currentSecondDimension + 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension+2][currentSecondDimension-2]
    else if ((board[currentFirstDimension+1][currentSecondDimension-1] == 'o' ||
             board[currentFirstDimension+1][currentSecondDimension-1] == 'O') &&
             currentFirstDimension + 2 == newFirstDimension && currentSecondDimension - 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension+1][currentSecondDimension-1] = ' ';
        //Decrement player 1 score
        player1Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension+2][currentSecondDimension+2]
    else if ((board[currentFirstDimension+1][currentSecondDimension+1] == 'o' ||
              board[currentFirstDimension+1][currentSecondDimension+1] == 'O') &&
             currentFirstDimension + 2 == newFirstDimension && currentSecondDimension + 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension+1][currentSecondDimension+1] = ' ';
        //Decrement player 1 score
        player1Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //Check if the move is [currentFirstDimension-1][currentSecondDimension-1] and anotherJump is false
    else if (currentFirstDimension - 1 == newFirstDimension && currentSecondDimension - 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //Check if the move is [currentFirstDimension-1][currentSecondDimension+1] and anotherJump is false
    else if (currentFirstDimension - 1 == newFirstDimension && currentSecondDimension + 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension-2][currentSecondDimension-2]
    else if ((board[currentFirstDimension-1][currentSecondDimension-1] == 'o' ||
             board[currentFirstDimension-1][currentSecondDimension-1] == 'O') &&
             currentFirstDimension - 2 == newFirstDimension && currentSecondDimension - 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension-1][currentSecondDimension-1] = ' ';
        //Decrement player 2 score
        player1Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension-2][currentSecondDimension+2]
    else if ((board[currentFirstDimension-1][currentSecondDimension+1] == 'o' ||
              board[currentFirstDimension-1][currentSecondDimension+1] == 'O') &&
             currentFirstDimension - 2 == newFirstDimension && currentSecondDimension + 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension-1][currentSecondDimension+1] = ' ';
        //Decrement player 2 score
        player1Score--;
        //Move the position
        board[newFirstDimension][newSecondDimension] = 'X';
        return true;
    }
    //If anotherjump is true then it should have made another jump
    else if (anotherJump == true)
    {
        cout << "That move was not a jump" << endl;
        return false;
    }
    //Else the move is an invalid move
    else
    {
        cout << "The move requested was an invalid move" << endl;
        return false;
    }
    return false;
}

//Method to move a regular player 1 piece up the board
/**
 * @brief Game::moveRegularP1Up
 *  Moves the regular piece for player 1 up the board
 *
 *  This method works nearly identical to the moveRegularP2Down method, but will instead
 *  move the pieces "up" if they are valid. We mean that a piece moves up (for P1) or down (for P2)
 *  because it is what can be seen from the screen, where the player 1 pieces move towards the top
 *  of the screen and the player 2 pieces move down the screen. Similarly to the other move methods,
 *  this method will check to see if the move is within the dimensions of the board (is the destination
 *  spot a legal spot)and will check to see if the spot isn't already occupied by a friendly piece. It
 *  will also check to see if the piece can make a jump and it will also check to see if the piece can
 *  make any subsequent jumps after the initial jump, where the game will force the player to make the jump.
 *
 * @param newFirstDimension
 * @param currentFirstDimension
 * @param newSecondDimension
 * @param currentSecondDimension
 * @return true if the move is valid, otherwise it will be false and an error appears
 */
bool Game::moveRegularP1Up(int newFirstDimension, int currentFirstDimension, int newSecondDimension,
                           int currentSecondDimension)
{
    //Check if the new dimensions are out of range of a move
    if (newFirstDimension < currentFirstDimension - 2 || newSecondDimension < currentSecondDimension - 2 ||
            newSecondDimension > currentSecondDimension + 2)
    {
        cout << "That is not a valid move" << endl;
        return false;
    }
    //Check if the move is [currentFirstDimension-1][currentSecondDimension-1] and anotherJump is false
    else if (currentFirstDimension - 1 == newFirstDimension && currentSecondDimension - 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 0)
        {
            board[newFirstDimension][newSecondDimension] = 'O';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'o';
        }
        return true;
    }
    //Check if the move is [currentFirstDimension-1][currentSecondDimension+1] and anotherJump is false
    else if (currentFirstDimension - 1 == newFirstDimension && currentSecondDimension + 1 == newSecondDimension &&
             anotherJump == false)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 0)
        {
            board[newFirstDimension][newSecondDimension] = 'O';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'o';
        }
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension-2][currentSecondDimension-2]
    else if ((board[currentFirstDimension-1][currentSecondDimension-1] == 'x' ||
             board[currentFirstDimension-1][currentSecondDimension-1] == 'X') &&
             currentFirstDimension - 2 == newFirstDimension && currentSecondDimension - 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension-1][currentSecondDimension-1] = ' ';
        //Decrement player 2 score
        player2Score--;
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 0)
        {
            board[newFirstDimension][newSecondDimension] = 'O';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'o';
        }
        return true;
    }
    //Check if the move is to jump a player and move [currentFirstDimension-2][currentSecondDimension+2]
    else if ((board[currentFirstDimension-1][currentSecondDimension+1] == 'x' ||
              board[currentFirstDimension-1][currentSecondDimension+1] == 'X') &&
             currentFirstDimension - 2 == newFirstDimension && currentSecondDimension + 2 == newSecondDimension)
    {
        //Set the current position to blank
        board[currentFirstDimension][currentSecondDimension] = ' ';
        //Remove the other players piece from the board
        board[currentFirstDimension-1][currentSecondDimension+1] = ' ';
        //Decrement player 2 score
        player2Score--;
        //Move the position
        //Check if needs to be kinged
        if (newFirstDimension == 0)
        {
            board[newFirstDimension][newSecondDimension] = 'O';
        }
        else
        {
            board[newFirstDimension][newSecondDimension] = 'o';
        }
        return true;
    }
    //If anotherjump is true then it must make another jump
    else if (anotherJump == true)
    {
        cout << "That move was not a jump" << endl;
        return false;
    }
    //Else the move is an invalid move
    else
    {
        cout << "The move requested was an invalid move" << endl;
        return false;
    }
    return false;
}

//Method to convert the second dimension from a character to an integer
/**
 * @brief Game::convertCharDimensionToInt
 *  This method converts the second dimension from a character to an integer
 *
 *  The method receives the character (the coordinate) of the board, rather the letter
 *  corresponding to 1/2 of the coordinates and will convert the value into an integer
 *  such that the application can process the information in finding out the move.
 * @param secondDimension a coodinate that corresponds to a move
 * @return A successful conversion in processing the move of a player
 */
int Game::convertCharDimensionToInt(char secondDimension)
{
    if (secondDimension == 'A' || secondDimension == 'a')
    {
        return 0;
    }
    else if (secondDimension == 'B' || secondDimension == 'b')
    {
        return 1;
    }
    else if (secondDimension == 'C' || secondDimension == 'c')
    {
        return 2;
    }
    else if (secondDimension == 'D' || secondDimension == 'd')
    {
        return 3;
    }
    else if (secondDimension == 'E' || secondDimension == 'e')
    {
        return 4;
    }
    else if (secondDimension == 'F' || secondDimension == 'f')
    {
        return 5;
    }
    else if (secondDimension == 'G' || secondDimension == 'g')
    {
        return 6;
    }
    else if (secondDimension == 'H' || secondDimension == 'h')
    {
        return 7;
    }
    else
    {
        return -1;
    }
}

//Method to check if the player can jump another player
/**
 * @brief Game::canJumpPlayer
 * A method that checks to see if a player can jump another player
 *
 * This method receives a parameter that tells the method what the current position is, which
 * then the application will use to check to see if any of the adjacent pieces are enemy pieces.
 * First the game will determine if the current piece is a King piece or a regular piece. Then, it
 * will scan to see if there is an opponent's piece adjacent to them, meaning that there is a
 * possibility that the player can make a jump. Once the game detects that an opponent piece is
 * next to them, it will check the piece adjacent to the opponent piece and make sure that the piece
 * adjacent to them is empty; bear in mind, that the application will also keep track to see if the
 * jump is legal, that is, the piece can safely jump a player and still be within the board's
 * dimensions. It will run the same tests for each type of piece (the P1 regular, P2 regular, P1 King,
 * and the P2 King), where the King pieces function slightly different than the regular pieces. The King
 * can jump in any direction, so it then has to check every adjacent piece to see if it can jump.
 * Meanwhile, the regular pieces only need to check above them (player 1 regular) or below them (player
 * 2 regular).
 *
 * @param currentPos
 * @return true if there is a player and there can be a jump, otherwise it will return false
 */
bool Game::canJumpPlayer(char *currentPos)
{
    //Get current dimensions for board
    int currentFirstDimension = currentPos[0] - '0';
    int currentSecondDimension = convertCharDimensionToInt(currentPos[1]);

    //Grab the current piece to check if its a king or regular piece
    char currentPiece = board[currentFirstDimension][currentSecondDimension];

    //Using current piece find out if there is another piece that can be jumped
    //Check player 1 reg
    if (currentPiece == 'o')
    {
        //Check for a opponent piece in an adjacent spot above current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension - 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension-1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension+1] == ' ')
                {
                    return true;
                }
            }
        }
        //Else there is no opponent
        return false;
    }
    //Check player 1 king
    else if (currentPiece == 'O')
    {
        //Check for a opponent piece in an adjacent spot above current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension - 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension-1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension+1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the left
        opponentSpotFirstDimension = currentFirstDimension + 1;
        opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension <= 7 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension-1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension+1] == ' ')
                {
                    return true;
                }
            }
        }
        //Else there is no opponent
        return false;
    }
    //Check if player 2 reg
    else if (currentPiece == 'x')
    {
        //Check for a opponent piece in an adjacent spot below current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension + 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension <= 7 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension-1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension+1] == ' ')
                {
                    return true;
                }
            }
        }
        //Else there is no opponent
        return false;
    }
    //Check if player 2 king
    else if (currentPiece == 'X')
    {
        //Check for a opponent piece in an adjacent spot below current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension + 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension <= 7 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension-1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension+1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the left
        opponentSpotFirstDimension = currentFirstDimension - 1;
        opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension-1] == ' ')
                {
                    return true;
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension+1] == ' ')
                {
                    return true;
                }
            }
        }
        //Else there is no opponent
        return false;
    }
    //Else error
    else
    {
        cout << "SHOULD NEVER GET HERE" << endl;
        return false;
    }
    return false;
}

//Method to check if the player can jump another player
/**
 * @brief Game::jumpPos
 *  Checks if the player can jump another player
 *
 *  This method is more or less a decider that decides whether or not a player's
 *  piece can be jumped. Similar to the canJumpPlayer method it largely does the same
 *  checks to see if the jump that can be made is legal, and if it's legal, then the
 *  piece will jump, otherwise, it will not jump anc continue the game. This is
 *  largely used to see if another piece can be jumped after the initial jump was made.
 * @param currentPos
 * @return the new position of the current piece since it jumped, and it must relay the information
 *  back to the board.
 */
string Game::jumpPos(char *currentPos)
{
    //Get current dimensions for board
    int currentFirstDimension = currentPos[0] - '0';
    int currentSecondDimension = convertCharDimensionToInt(currentPos[1]);

    //Grab the current piece to check if its a king or regular piece
    char currentPiece = board[currentFirstDimension][currentSecondDimension];

    //Using current piece find out if there is another piece that can be jumped
    //Check player 1 reg
    if (currentPiece == 'o')
    {
        //Check for a opponent piece in an adjacent spot above current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension - 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension-1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension-1);
                    ostringstream np;
                    np << opponentSpotFirstDimension-1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension+1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension+1);
                    ostringstream np;
                    np << opponentSpotFirstDimension-1 << column;
                    return np.str();
                }
            }
        }
        //Else there is no opponent
        return "";
    }
    //Check player 1 king
    else if (currentPiece == 'O')
    {
        //Check for a opponent piece in an adjacent spot above current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension - 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension-1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension-1);
                    ostringstream np;
                    np << opponentSpotFirstDimension-1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension+1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension+1);
                    ostringstream np;
                    np << opponentSpotFirstDimension-1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the left
        opponentSpotFirstDimension = currentFirstDimension + 1;
        opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension <= 7 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension-1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension-1);
                    ostringstream np;
                    np << opponentSpotFirstDimension+1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'x' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'X')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension+1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension+1);
                    ostringstream np;
                    np << opponentSpotFirstDimension+1 << column;
                    return np.str();
                }
            }
        }
        //Else there is no opponent
        return "";
    }
    //Check if player 2 reg
    else if (currentPiece == 'x')
    {
        //Check for a opponent piece in an adjacent spot below current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension + 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension <= 7 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension-1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension-1);
                    ostringstream np;
                    np << opponentSpotFirstDimension+1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension+1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension+1);
                    ostringstream np;
                    np << opponentSpotFirstDimension+1 << column;
                    return np.str();
                }
            }
        }
        //Else there is no opponent
        return "";
    }
    //Check if player 2 king
    else if (currentPiece == 'X')
    {
        //Check for a opponent piece in an adjacent spot below current piece and to the left
        int opponentSpotFirstDimension = currentFirstDimension + 1;
        int opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension <= 7 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension-1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension-1);
                    ostringstream np;
                    np << opponentSpotFirstDimension+1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot below current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension + 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension+1][opponentSpotSecondDimension+1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension+1);
                    ostringstream np;
                    np << opponentSpotFirstDimension+1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the left
        opponentSpotFirstDimension = currentFirstDimension - 1;
        opponentSpotSecondDimension = currentSecondDimension - 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension - 1 >= 0 ||
                opponentSpotSecondDimension - 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension-1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension-1);
                    ostringstream np;
                    np << opponentSpotFirstDimension-1 << column;
                    return np.str();
                }
            }
        }
        //Check for a opponent piece in an adjacent spot above current piece and to the right
        opponentSpotSecondDimension = currentSecondDimension + 1;
        //Check to make sure not out of bounds
        if (opponentSpotFirstDimension >= 0 || opponentSpotSecondDimension >= 0 || opponentSpotSecondDimension < 8 ||
                opponentSpotFirstDimension - 1 >= 0 || opponentSpotSecondDimension + 1 >= 0 ||
                opponentSpotSecondDimension + 1 < 8)
        {
            //Check to see if there is an opponent here
            if (board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'o' ||
                    board[opponentSpotFirstDimension][opponentSpotSecondDimension] == 'O')
            {
                //Now check if the piece on the corner is available
                if (board[opponentSpotFirstDimension-1][opponentSpotSecondDimension+1] == ' ')
                {
                    //Get new position
                    char column = convertIntToChar(opponentSpotSecondDimension+1);
                    ostringstream np;
                    np << opponentSpotFirstDimension-1 << column;
                    return np.str();
                }
            }
        }
        //Else there is no opponent
        return "";
    }
    //Else error
    else
    {
        cout << "SHOULD NEVER GET HERE" << endl;
        return "";
    }
    return "";
}

//Method to convert an integer to corresponding character on board
/**
 * @brief Game::convertIntToChar
 *  Convert an integer to a corresponding character on the board
 *
 *  After the game makes its computations to authenticate a valid move for a given
 *  player, the game does the move, then checks to see if a jump can be made (or has
 *  been made). Then after it finishes the calculations, it then converts the integer
 *  that was generated earlier back to its corresponding character that is part of the
 *  move coordinates when making a move.
 * @param num
 * @return the coordinate of the board for a move
 */
char Game::convertIntToChar(int num)
{
    switch (num)
    {
    case 0:
        return 'A';
    case 1:
        return 'B';
    case 2:
        return 'C';
    case 3:
        return 'D';
    case 4:
        return 'E';
    case 5:
        return 'F';
    case 6:
        return 'G';
    case 7:
        return 'H';
    default:
        return 'X';
    }
}
