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
    QGraphicsScene *s = new QGraphicsScene();
    computer.addGrid(s);
    ui->gv->setScene(s);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendButton_clicked()
{
    if (playerTurn == 1)
    {
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
        int originalPlayer2Score = computer.player2Score;

        //Send data to board in order to move
        bool successfulTurn = computer.makeAMove(playerTurn, pieceToMove, placeToMoveTo);
        computer.displayBoard(computer.player1Score, computer.player2Score);
        computer.updateGrid(ui->gv->scene());
        //computer.
        //Check for finish
        if (computer.player2Score == 0)
        {
            cout << "Congratulations player 1 you have WON!" << endl;
            exit(0);
        }

        //Clear the text for the next move
        ui->Piece->clear();
        ui->Position->clear();

        //If there was a score decrement then check if there is another jump for the player
        if (computer.player2Score != originalPlayer2Score)
        {
            //a player scored
            computer.anotherJump = computer.canJumpPlayer(placeToMoveTo);
        }
        else
        {
            computer.anotherJump = false;
        }

        //Change the player turn if successfull turn
        if (successfulTurn == true && computer.anotherJump == false)
        {
            playerTurn++;
            if (playerTurn > 2)
            {
                playerTurn = 1;
            }
        }
        else if (computer.anotherJump == true)
        {
            cout << "Player " << playerTurn << " please make another jump" << endl;
        }
        else if (successfulTurn == false)
        {
            cout << "Player " << playerTurn << " please try again" << endl;
        }
    }

    //Player 2's turn
    if (playerTurn == 2)
    {
        //Check all the moves for the player
        computer.checkAllComputerMoves();

        //Decide which move to make
        string moves = computer.decider();
        cout << moves << endl;

        //Parse the moves to send to the computer
        char *bothPos = new char[5];
        strcpy(bothPos, moves.c_str());
        char *sepPos[2];
        char *seperator;
        seperator = strtok(bothPos, "/");
        for (int i = 0; i < 2; i++)
        {
            sepPos[i] = seperator;
            seperator = strtok(NULL, "/");
        }

        int originalPlayer1Score = computer.player1Score;

        //Have the computer move
        //Send data to board in order to move
        bool successfulPCTurn = computer.makeAMove(playerTurn, sepPos[0], sepPos[1]);
        computer.displayBoard(computer.player1Score, computer.player2Score);
        computer.updateGrid(ui->gv->scene());

        //Check for finish
        if (computer.player1Score == 0)
        {
            cout << "Congratulations player 2 you have WON!" << endl;
            exit(0);
        }

        //If there was a score decrement then check if there is another jump for the player
        if (computer.player1Score != originalPlayer1Score)
        {
            //a player scored
            computer.anotherJump = computer.canJumpPlayer(sepPos[1]);
            while(computer.anotherJump == true)
            {
                string newPos = computer.jumpPos(sepPos[1]);
                char *position = new char[2];
                strcpy(position, newPos.c_str());
                computer.makeAMove(playerTurn, sepPos[1], position);
                sepPos[1] = position;
                computer.anotherJump = computer.canJumpPlayer(sepPos[1]);
            }
        }
        else
        {
            computer.anotherJump = false;
            computer.updateGrid(ui->gv->scene());
        }

        //Change the player turn if successfull turn
        if (successfulPCTurn == true && computer.anotherJump == false)
        {
            playerTurn++;
            if (playerTurn > 2)
            {
                playerTurn = 1;
            }
        }

        //Remove all data from moveAvailable
        computer.removeData();
    }
    computer.updateGrid(ui->gv->scene());
}

void MainWindow::on_StartButton_clicked()
{
    //Just display the board
    game.displayBoard(game.player1Score, game.player2Score);
    //Set the player turn to player 1
    game.updateGrid(ui->gv->scene());
    playerTurn = 1;
}

void MainWindow::on_ExitButton_clicked()
{
    //Exit
    exit(0);
}
