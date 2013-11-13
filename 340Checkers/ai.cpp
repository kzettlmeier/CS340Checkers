#include "ai.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

AI::AI()
{
}

//Method to check all possible moves for computer
void AI::checkAllComputerMoves()
{
    cout << availableMoves.size() << endl;
    //First grab all the positions for every computer piece on the board
    for (int i = 0; i < BOARD_LENGTH; i++)
    {
        for (int j = 0; j < BOARD_LENGTH; j++)
        {
            //Check for all normal x's
            if (board[i][j] == 'x')
            {
                //Keep a count of the number of new moves available (without jumps)
                int count = 0;

                //Keep a count of the number of jumps available
                int countJumps = 0;

                //Get current position
                char column = convertIntToChar(j);
                ostringstream cp;
                cp << i << column;
                string position(cp.str());
                //Convert string to char*
                moves positionToMove;
                char *var = new char[2];
                strcpy(var, position.c_str());
                positionToMove.currentPosition = var;
                var = NULL;
                //Set the newpositions to NULL
                for (int k = 0; k < 4; k++)
                {
                    positionToMove.newPositions[k] = NULL;
                    positionToMove.jumps[k] = NULL;
                }

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
                        char *var = new char[2];
                        strcpy(var, newPosition.c_str());
                        positionToMove.newPositions[count] = var;
                        var = NULL;
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
                                np << i+2 << column;
                                string newPosition(np.str());
                                //Convert string to char*
                                char *var = new char[2];
                                strcpy(var, newPosition.c_str());
                                positionToMove.jumps[countJumps] = var;
                                var = NULL;
                                countJumps++;
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
                        char *var = new char[2];
                        strcpy(var, newPosition.c_str());
                        positionToMove.newPositions[count] = var;
                        var = NULL;
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
                                char *var = new char[2];
                                strcpy(var, newPosition.c_str());
                                positionToMove.jumps[countJumps] = var;
                                var = NULL;
                                countJumps++;
                            }
                        }
                    }
                }

                delete[] var;
                //Add to vector if there a position that can move
                if (count != 0 || countJumps != 0)
                {
                    //Add positions to vector
                    availableMoves.push_back(positionToMove);
                }
            }
            //Check for all kings
            else if (board[i][j] == 'X')
            {
                //Keep a count of the number of new moves available (without jumps)
                int count = 0;

                //Keep a count of the number of jumps available
                int countJumps = 0;

                //Get current position
                char column = convertIntToChar(j);
                ostringstream cp;
                cp << i << column;
                string position(cp.str());
                //Convert string to char*
                moves positionToMove;
                char *var = new char[2];
                strcpy(var, position.c_str());
                positionToMove.currentPosition = var;
                var = NULL;

                //Set the newpositions to NULL
                for (int k = 0; k < 4; k++)
                {
                    positionToMove.newPositions[k] = NULL;
                    positionToMove.jumps[k] = NULL;
                }

                //First check if the pieces can move down
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
                        char *var = new char[2];
                        strcpy(var, newPosition.c_str());
                        positionToMove.newPositions[count] = var;
                        var = NULL;
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
                                np << i+2 << column;
                                string newPosition(np.str());
                                //Convert string to char*
                                char *var = new char[2];
                                strcpy(var, newPosition.c_str());
                                positionToMove.jumps[countJumps] = var;
                                var = NULL;
                                countJumps++;
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
                        char *var = new char[2];
                        strcpy(var, newPosition.c_str());
                        positionToMove.newPositions[count] = var;
                        var = NULL;
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
                                char *var = new char[2];
                                strcpy(var, newPosition.c_str());
                                positionToMove.jumps[countJumps] = var;
                                var = NULL;
                                countJumps++;
                            }
                        }
                    }
                }

                //Now check all up moves
                if (i-1 > -1 && j-1 > -1)
                {
                    if (board[i-1][j-1] == ' ')
                    {
                        //Get new position
                        column = convertIntToChar(j-1);
                        ostringstream np;
                        np << i-1 << column;
                        string newPosition(np.str());
                        //Convert string to char*
                        char *var = new char[2];
                        strcpy(var, newPosition.c_str());
                        positionToMove.newPositions[count] = var;
                        var = NULL;
                        count++;
                    }
                    else if (board[i-1][j-1] == 'o' || board[i-1][j-1] == 'O')
                    {
                        //Check if the position after the user is open for a jump
                        if (i - 2 > -1 && j - 2 > -1)
                        {
                            if (board[i-2][j-2] == ' ')
                            {
                                //Get new position
                                column = convertIntToChar(j-2);
                                ostringstream np;
                                np << i-2 << column;
                                string newPosition(np.str());
                                //Convert string to char*
                                char *var = new char[2];
                                strcpy(var, newPosition.c_str());
                                positionToMove.jumps[countJumps] = var;
                                var = NULL;
                                countJumps++;
                            }
                        }
                    }
                    if (i-1 > -1 && j+1 < BOARD_LENGTH)
                    {
                        if (board[i-1][j+1] == ' ')
                        {
                            //Get new position
                            column = convertIntToChar(j+1);
                            ostringstream np;
                            np << i-1 << column;
                            string newPosition(np.str());
                            //Convert string to char*
                            char *var = new char[2];
                            strcpy(var, newPosition.c_str());
                            positionToMove.newPositions[count] = var;
                            var = NULL;
                            count++;
                        }
                        else if (board[i-1][j+1] == 'o' || board[i-1][j+1] == 'O')
                        {
                            if (i-2 > -1 && j+2 < BOARD_LENGTH)
                            {
                                if (board[i-2][j+2] == ' ')
                                {
                                    //Get new position
                                    column = convertIntToChar(j+2);
                                    ostringstream np;
                                    np << i-2 << column;
                                    string newPosition(np.str());
                                    //Convert string to char*
                                    char *var = new char[2];
                                    strcpy(var, newPosition.c_str());
                                    positionToMove.jumps[countJumps] = var;
                                    var = NULL;
                                    countJumps++;
                                }
                            }
                        }
                    }
                    delete[] var;
                    //Add to vector if there a position that can move
                    if (count != 0)
                    {
                        //Add positions to vector
                        availableMoves.push_back(positionToMove);
                    }
                }
            }
        }
    }

    //FOR TESTING PURPOSES ONLY
    for (int i = 0; (unsigned)i < availableMoves.size(); i++)
    {
        moves listing = availableMoves.at(i);
        cout << listing.currentPosition << " ";
        for (int j = 0; j < 4; j++)
        {
            if (listing.newPositions[j] != NULL)
            {
                cout << listing.newPositions[j] << " ";
            }
            if (listing.jumps[j] != NULL)
            {
                cout << listing.jumps[j] << " ";
            }
        }
        cout << endl;
    }
}

//Method to decide which move to take
string AI::decider()
{
    //First check if there are any jumps
    int numJumps = 0;
    int numRegJumps = 0;
    for (int i = 0; (unsigned)i < availableMoves.size(); i++)
    {
        moves jumpPos = availableMoves.at(i);
        for (int j = 0; j < 4; j++)
        {
            if (jumpPos.jumps[j] != NULL)
            {
                numJumps++;
            }
            if (jumpPos.newPositions[j] != NULL)
            {
                numRegJumps++;
            }
        }
    }
    if (numJumps != 0)
    {
        int takeJump = rand() % numJumps + 1;
        for (int i = 0; (unsigned)i < availableMoves.size(); i++)
        {
            moves jumpPos = availableMoves.at(i);
            for (int j = 0; j < 4; j++)
            {
                if (jumpPos.jumps[j] != NULL)
                {
                    if (takeJump == 1)
                    {
                        ostringstream o;
                        o << jumpPos.currentPosition << "/" << jumpPos.jumps[j];
                        return o.str();
                    }
                    takeJump--;
                }
            }
        }
    }
    int move = rand() % numRegJumps + 1;
    for (int i = 0; (unsigned)i < availableMoves.size(); i++)
    {
        moves pos = availableMoves.at(i);
        for (int j = 0; j < 4; j++)
        {
            if (pos.newPositions[j] != NULL)
            {
                if (move == 1)
                {
                    ostringstream o;
                    o << pos.currentPosition << "/" << pos.newPositions[j];
                    return o.str();
                }
                move--;
            }
        }
    }
    return "";
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

//Remove data from moveAvailable
void AI::removeData()
{
    availableMoves.clear();
}
