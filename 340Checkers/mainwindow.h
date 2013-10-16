/*
 * This is the UI Header, all UI objects are declared here
 * Also declared here is the game object and the player who's turn
 *  is up is also stored here.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Game game;
    int playerTurn;

private slots:
    void on_SendButton_clicked();

    void on_StartButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
