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
                board[i][j] = 'X';
            }
            else
            {
                board[i][j] = ' ';
            }

        }
    }
}

//Method to display the board in command line
void Board::displayBoard()
{
    //Show the board
    for (int i = 0; i < BOARD_LENGTH; i++)
    {
        for (int j = 0; j < BOARD_LENGTH; j++)
        {
            cout << "[" << board[i][j] << "]";
            //If last column, end the line
            if (j == BOARD_LENGTH - 1)
            {
                cout << endl;
            }
        }
    }
}
