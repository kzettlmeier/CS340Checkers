/**
 *  \file mainwindow.cpp
 *   The main interface of the UI
 *
 *  This is where the UI does its work. It is used to start the game, make the moves and quitting the
 *  application. Most of what the UI has to access, such as signals, slots, and widgets are located here.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *  \date December 2013
 *  \bug No major bugs were found upon testing
 *
 *  \namespace std using namespace identifier
 */


/*
 * This is where all the UI does its work.
 * Starting the game as well as making the moves and quiting.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

/**
 * @brief MainWindow::MainWindow
 *  The main method to bring up the UI screen.
 * @param parent
 *
 *  \fn addGrid creates the grid that will display the board
 *  \param s a QGraphicsScene element
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *s = new QGraphicsScene();
    computer.addGrid(s);
    ui->gv->setScene(s);
}

/**
 * @brief MainWindow::~MainWindow
 *  Closes the UI window once the application is exited
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_SendButton_clicked
 *  Sends the player's move to the game logic
 *
 *  This button (originally) would take the player's current piece selection
 *  and a destination location and send the information to the game logic,
 *  which would run and see if the move is valid or not. If a move can be made,
 *  then the game will do the move, and update the board with the new move; otherwise,
 *  the game will report an error message to the current player and tell them what is wrong.
 */
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
        usleep((useconds_t)100000);// pause a moment
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
        usleep((useconds_t)100000);// pause a moment
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
                usleep((useconds_t)100000);// pause a moment
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
    char b [8];
    snprintf(b, sizeof(b), "P1: %d", computer.player1Score);
    ui->p1score->setText(b);
    snprintf(b, sizeof(b), "P2: %d", computer.player2Score);
    ui->p2score->setText(b);
}

/**
 * @brief MainWindow::on_StartButton_clicked
 *  Button that starts the game
 *
 *  When the start button is clicked, the game board is initalized and the board is
 *  created, indicating both players' pieces, and the scores of each player. Then, it
 *  will tell player 1 to begin the game.
 */
void MainWindow::on_StartButton_clicked()
{
    //Just display the board
    game.displayBoard(game.player1Score, game.player2Score);
    //Set the player turn to player 1
    game.updateGrid(ui->gv->scene());
    playerTurn = 1;
    ui->p1score->setText("P1: 12");
    ui->p2score->setText("P2: 12");
}

/**
 * @brief MainWindow::on_ExitButton_clicked
 *  Exits the application on click
 *
 *  Clicking the exit button will exit the game and close the program.
 */
void MainWindow::on_ExitButton_clicked()
{
    //Exit
    exit(0);
}
