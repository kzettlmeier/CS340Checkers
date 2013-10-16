/*
 * This is where the board is initialized
 */

#include "board.h"
#include <iostream>

using namespace std;

//Constructor
Board::Board()
{
    //Initialize board
    for (int i = 0; i < BOARD_LENGTH; i++)
    {
        for (int j = 0; j < BOARD_LENGTH; j++)
        {
            //Place an X on the black spaces of the board for representation
            if ((j % 2 != 0 && i % 2 == 0) || (j % 2 == 0 && i % 2 != 0))
            {
                board[i][j] = '#';
            }
            else
            {
                //Player 2
                if (i < 3)
                {
                    board[i][j] = 'x';
                }
                //Player 1
                else if (i > 4)
                {
                    board[i][j] = 'o';
                }
                //Blank spots
                else
                {
                    board[i][j] = ' ';
                }
            }
        }
    }
}

//Method to display the board in command line
void Board::displayBoard(int player1Score, int player2Score)
{
    //Show the board
    cout << "   A  B  C  D  E  F  G  H" << endl;
    for (int i = 0; i < BOARD_LENGTH; i++)
    {
        for (int j = 0; j < BOARD_LENGTH; j++)
        {
            if (j == 0)
            {
                cout << i << " ";
            }
            cout << "[" << board[i][j] << "]";
            //If last column, end the line
            if (j == BOARD_LENGTH - 1)
            {
                cout << endl;
            }
        }
    }
    cout << "Player 1 score: " << player1Score << endl;
    cout << "Player 2 score: " << player2Score << endl;
    cout << endl;
}
