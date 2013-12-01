/**
 *  \file mainwindow.h
 *  Header file for the UI
 *
 *  This is the header file for the UI. It includes all of the objects that
 *  the UI is in charge of and all of the objects that are used by the UI are
 *  stored in this file. The current player's turn and some game objects are
 *  declared here, since we felt it was necessary.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *  \date December 2013
 *  \bug No major bugs were found upon testing
 *
 *  \namespace Ui using the namespace Ui identifier
 *  \class MainWindow the MainWindow class is part of the Ui namespace
 */

/*
 * This is the UI Header, all UI objects are declared here
 * Also declared here is the game object and the player who's turn
 *  is up is also stored here.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "game.h"
#include "ai.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 *  The MainWindow class inherits the QMainWindow public class
 *
 *  This class contains the UI's objects and their declarations, while
 *  also containing some of the game's objects like the player's turn
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Game game;
    AI computer;
    int playerTurn;

private slots:
    void on_SendButton_clicked();

    void on_StartButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
