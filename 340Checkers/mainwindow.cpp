/*
 * This is where all the UI does its work.
 * Starting the game as well as making the moves and quiting.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendButton_clicked()
{
    //Say whos turn
    cout << "It is now player " << playerTurn << "s turn" << endl;

    //When clicked, send the piece that you want to move
    //as well as the new position that you want that piece to move to
    QString piece = ui->Piece->text();
    QString position = ui->Position->text();

    //Convert to char *
    QByteArray byteArray = piece.toLocal8Bit();
    char *pieceToMove = byteArray.data();
    byteArray = position.toLocal8Bit();
    char *placeToMoveTo = byteArray.data();

    cout << "Trying to move from " << pieceToMove << " to " << placeToMoveTo << endl;

    //Store the original score in case of a jump
    int originalPlayer1Score = game.player1Score;
    int originalPlayer2Score = game.player2Score;

    //Send data to board in order to move
    bool successfulTurn = game.makeAMove(playerTurn, pieceToMove, placeToMoveTo);
    game.displayBoard(game.player1Score, game.player2Score);

    //Check for finish
    if (game.player1Score == 0)
    {
        cout << "Congratulations player 2 you have WON!" << endl;
        exit(0);
    }
    else if (game.player2Score == 0)
    {
        cout << "Congratulations player 1 you have WON!" << endl;
        exit(0);
    }

    //Clear the text for the next move
    ui->Piece->clear();
    ui->Position->clear();

    //If there was a score decrement then check if there is another jump for the player
    if (game.player1Score != originalPlayer1Score || game.player2Score != originalPlayer2Score)
    {
        //a player scored
        game.anotherJump = game.canJumpPlayer(placeToMoveTo);
    }
    else
    {
        game.anotherJump = false;
    }

    //Change the player turn if successfull turn
    if (successfulTurn == true && game.anotherJump == false)
    {
        playerTurn++;
        if (playerTurn > 2)
        {
            playerTurn = 1;
        }
    }
    else if (game.anotherJump == true)
    {
        cout << "Player " << playerTurn << " please make another jump" << endl;
    }
    else if (successfulTurn == false)
    {
        cout << "Player " << playerTurn << " please try again" << endl;
    }
}

void MainWindow::on_StartButton_clicked()
{
    //Just display the board
    game.displayBoard(game.player1Score, game.player2Score);
    //Set the player turn to player 1
    playerTurn = 1;
}

void MainWindow::on_ExitButton_clicked()
{
    //Exit
    exit(0);
}
