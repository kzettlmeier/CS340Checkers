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
