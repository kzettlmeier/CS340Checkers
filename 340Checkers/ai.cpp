#include "ai.h"
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

AI::AI()
{
}

//Method to check all possible moves for computer
void AI::checkAllComputerMoves()
{
    //First grab all the positions for every computer piece on the board
    for (int i = 0; i < BOARD_LENGTH; i++)
    {
        for (int j = 0; j < BOARD_LENGTH; j++)
        {
            if (board[i][j] == 'x')
            {
                int count = 0;

                //Get current position
                char column = convertIntToChar(j);
                ostringstream cp;
                cp << i << column;
                string position(cp.str());
                //Convert string to char*
                moves positionToMove;
                positionToMove.currentPosition = position.c_str();
                //Set the newpositions to NULL
                for (int k = 0; k < 4; k++)
                {
                    positionToMove.newPositions[k] = NULL;
                }
                cout << positionToMove.currentPosition << endl;

                //Check if the piece can move down to either a normal move or a jump
                //First check if the position to move to is on the board
                if (i+1 < BOARD_LENGTH && j-1 > -1)
                {
                    if (board[i+1][j-1] == ' ')
                    {
                        //Get new position
                        column = convertIntToChar(j-1);
                        ostringstream np;
                        np << i+1 << column;
                        string newPosition(np.str());
                        //Convert string to char*
                        positionToMove.newPositions[count] = newPosition.c_str();
                        count++;
                    }
                    else if (board[i+1][j-1] == 'o' || board[i+1][j-1] == 'O')
                    {
                        //Check if the position after the user is open for a jump
                        if (i + 2 < BOARD_LENGTH && j - 2 > -1)
                        {
                            if (board[i+2][j-2] == ' ')
                            {
                                //Get new position
                                column = convertIntToChar(j-2);
                                ostringstream np;
                                np << i+2 << j-2;
                                string newPosition(np.str());
                                //Convert string to char*
                                positionToMove.newPositions[count] = newPosition.c_str();
                                count++;
                            }
                        }
                    }
                }
                if (i+1 < BOARD_LENGTH && j+1 < BOARD_LENGTH)
                {
                    if (board[i+1][j+1] == ' ')
                    {
                        //Get new position
                        column = convertIntToChar(j+1);
                        ostringstream np;
                        np << i+1 << column;
                        string newPosition(np.str());
                        //Convert string to char*
                        positionToMove.newPositions[count] = newPosition.c_str();
                        count++;
                    }
                    else if (board[i+1][j+1] == 'o' || board[i+1][j+1] == 'O')
                    {
                        if (i+2 < BOARD_LENGTH && j+2 < BOARD_LENGTH)
                        {
                            if (board[i+2][j+2] == ' ')
                            {
                                //Get new position
                                column = convertIntToChar(j+2);
                                ostringstream np;
                                np << i+2 << column;
                                string newPosition(np.str());
                                //Convert string to char*
                                positionToMove.newPositions[count] = newPosition.c_str();
                                count++;
                            }
                        }
                    }
                }

                //Add to vector if there a position that can move
                if (count != 0)
                {
                    //Add positions to vector
                    availableMoves.push_back(positionToMove);
                }
            }
        }
    }

    for (int i = 0; i < availableMoves.size(); i++)
    {
        moves listing = availableMoves.at(i);
        cout << listing.currentPosition << " ";
        for (int j = 0; j < 4; j++)
        {
            if (listing.newPositions[j] != NULL)
            {
                cout << listing.newPositions[j] << " ";
            }
        }
        cout << endl;
    }
}

//Method to convert an integer to corresponding character on board
char AI::convertIntToChar(int num)
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
