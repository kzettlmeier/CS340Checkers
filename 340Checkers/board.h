#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
    static const int BOARD_LENGTH = 8;
    //BOARD_LENGTH + 1 because we want a border around the board
    char board[BOARD_LENGTH][BOARD_LENGTH];
public:
    Board();
    void displayBoard();
};

#endif // BOARD_H
