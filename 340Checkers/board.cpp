/**
 *  \file board.cpp
 *  This is where the board is initialized.
 *
 *  This contains everything that the board does, from initially generating the board to properly displaying the current board status (which is the
 *  current move). It is constantly refreshed whenever a new move is made.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *
 *  \bug No bugs were found with testing.
 */

/*
 * This is where the board is initialized
 */

#include "board.h"
#include <iostream>

/**
 * \namespace std using the std namespace identifier
 */
using namespace std;

//Constructor
/**
 * @brief Board::Board
 *  A Board constructor that initializes the board.
 */
Board::Board()
{
    //Initialize board
    for (int i = 0; i < BOARD_LENGTH; i++)
    {
        for (int j = 0; j < BOARD_LENGTH; j++)
        {
            tiles[i][j].y = i*SQ_S;
            tiles[i][j].x = j*SQ_S;
            //Place an # on the black spaces of the board for representation
            if ((j % 2 != 0 && i % 2 == 0) || (j % 2 == 0 && i % 2 != 0))
            {
                board[i][j] = '#';
                tiles[i][j].color = BLACK;
            }
            else
            {
                tiles[i][j].color = RED;
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
/**
 * @brief Board::displayBoard
 *  Displays the current Board with both players' scores (the remaining pieces)
 * @param player1Score The number of pieces left of player 1
 * @param player2Score The remaining pieces for player 2
 */
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

/**
 * @brief Board::addGrid
 *  This will generate the graphical grid and create a GUI with the visual board.
 * @param scene
 */
void Board::addGrid(QGraphicsScene *scene)
{
    QBrush redBrush(Qt::red);
    QBrush blackBrush(Qt::black);
    QPen blackPen(QColor(255, 255, 255));
    int x,y;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            x = tiles[i][j].x;
            y = tiles[i][j].y;
            //scene->foregroundBrush();
            //scene->addRect(QRectF(x,y,SQ_S,SQ_S));
            if (tiles[i][j].color == RED)
                scene->addRect(x,y,SQ_S,SQ_S, blackPen, redBrush);
            else
                scene->addRect(x,y,SQ_S,SQ_S, blackPen, blackBrush);

        }
    }

}

/**
 * @brief Board::updateGrid
 *  Updates the grid with the current turn and pieces remaining on the board.
 *
 *  The new things added onto this file are the different colors that represent the
 *  different pieces in the game. Also, the grid's coordinates that are used to make
 *  a player move are now visible on the board, making it easier to find locate a piece
 *  on the board.
 * @param scene A QGraphicsScene pointer that's used represent objects on the UI.
 */
void Board::updateGrid(QGraphicsScene *scene)
{
    QBrush redBrush(Qt::red);
    QBrush blackBrush(Qt::black);
    QBrush cyan(Qt::cyan);
    QBrush green(Qt::green);
    QBrush kx(Qt::blue);
    QBrush ko(Qt::black);
    QPen blackPen(QColor(255, 255, 255));
    int x,y,xp,yp;

    usleep((useconds_t)200000);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            x = j*SQ_S;
            y = i*SQ_S;
            xp = tiles[i][j].x + SQ_S/4;
            yp = tiles[i][j].y + SQ_S/4;

            if (tiles[i][j].color == RED)
                scene->addRect(x,y,SQ_S,SQ_S, blackPen, redBrush);
            else
                scene->addRect(x,y,SQ_S,SQ_S, blackPen, blackBrush);

            if(board[i][j] == 'x') {
                scene->addRect(xp,yp,SQ_S/2,SQ_S/2,blackPen,cyan);
                //cout<<"x at ("<<i<<", "<<j<<")\n"<<endl;
            }
            else if(board[i][j] == 'o') {
                scene->addRect(xp,yp,SQ_S/2,SQ_S/2,blackPen,green);
                //cout<<"o at ("<<i<<", "<<j<<")\n"<<endl;
            }
            else if(board[i][j] == 'X') {
                scene->addRect(xp,yp,SQ_S/2,SQ_S/2,blackPen,cyan);
                scene->addRect(xp+SQ_S/8,yp+SQ_S/8,SQ_S/4,SQ_S/4,blackPen,kx);
                //cout<<"o at ("<<i<<", "<<j<<")\n"<<endl;
            }
            else if(board[i][j] == 'O') {
                scene->addRect(xp,yp,SQ_S/2,SQ_S/2,blackPen,green);
                scene->addRect(xp+SQ_S/8,yp+SQ_S/8,SQ_S/4,SQ_S/4,blackPen,ko);
                //cout<<"o at ("<<i<<", "<<j<<")\n"<<endl;
            }

        }
    }

}
