/**
 *
 *  \file main.cpp
 *  \brief  This is the main class that starts the application.
 *
 *  \details This will start up the application and start up the game.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *  \date December 2013
 *  \bug No major bugs were found upon testing
 *  \warning If your computer does not contain the standard C libraries, such as 'stdlib.h', then the application may not run.
 *
 */

#include "mainwindow.h"
#include <QApplication>

using namespace std;

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    /**
     * @brief a
     * @return
     */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
