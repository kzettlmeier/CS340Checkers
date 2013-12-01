/**
 *  \file board.h
 *  The board header file
 *
 *  This is the board header file, this is where the board will be stored.
 *  This also store the board length, in which if you wanted a bigger board
 *  you can do it here.
 *  This is also where we have the display board function, which was was used
 *  to create the checkers game as a console application.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *
 *  \def BOARD_H
 *  Creates the board
 *  \def SQ_S
 *  Pre-defines the size of the square to about 40 pixels
 */

/*
 * This is the board header file, this is where the board will be stored.
 * This also store the board length, in which if you wanted a bigger board
 *  you can do it here.
 * This is also where we have the display board function, which was was used
 *  to create the checkers game as a console application.
 */
#ifndef BOARD_H
#define BOARD_H
#define SQ_S 40
#include <QGraphicsScene>
#include <QtGui>
#include <unistd.h>

/**
 * @brief The color enum
 * \struct sq
 *  A structure containing the values of a square, which include its x and y position and the color of the square.
 * \var x
 *  X coordinate
 * \var y
 *  Y coordinate
 */
enum color{RED,BLACK};
typedef struct sq{
    int x;
    int y;
    int color;
}sq;

/**
 * @brief The Board class
 *
 *  \fn displayBoard(int player1Score, intPlayer2Score)
 *  Displays the board with both player scores
 *
 *  \fn addGrid(QGraphicsScene *scene)
 *  Creates the grid
 *
 *  \fn updateGrid(QGraphicsScene *scene)
 *  Updates the graphical board
 */
class Board : public QGraphicsView
{
private:
public:
    sq tiles[8][8];
    static const int BOARD_LENGTH = 8;
    char board[BOARD_LENGTH][BOARD_LENGTH];
    Board();
    void displayBoard(int player1Score, int player2Score);
    void addGrid(QGraphicsScene *scene);
    void updateGrid(QGraphicsScene *scene);
};

#endif // BOARD_H
