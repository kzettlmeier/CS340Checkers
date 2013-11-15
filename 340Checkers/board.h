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

enum color{RED,BLACK};
typedef struct sq{
    int x;
    int y;
    int color;
}sq;

class Board
{
private:
public:
    sq tiles[8][8];
    static const int BOARD_LENGTH = 8;
    char board[BOARD_LENGTH][BOARD_LENGTH];
    Board();
    void displayBoard(int player1Score, int player2Score);
    void addGrid(QGraphicsScene *scene);
};

#endif // BOARD_H
