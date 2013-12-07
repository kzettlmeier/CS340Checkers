/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *SendButton;
    QLineEdit *Piece;
    QLineEdit *Position;
    QLabel *label;
    QLabel *label_2;
    QPushButton *StartButton;
    QPushButton *ExitButton;
    QGraphicsView *gv;
    QLabel *p1score;
    QLabel *p2score;
    QLabel *rows;
    QLabel *cols;
    QLabel *rows_2;
    QLabel *rows_3;
    QLabel *rows_5;
    QLabel *rows_6;
    QLabel *rows_7;
    QLabel *rows_8;
    QLabel *rows_9;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(725, 465);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setGeometry(QRect(30, 240, 80, 23));
        Piece = new QLineEdit(centralWidget);
        Piece->setObjectName(QStringLiteral("Piece"));
        Piece->setGeometry(QRect(20, 140, 113, 23));
        Position = new QLineEdit(centralWidget);
        Position->setObjectName(QStringLiteral("Position"));
        Position->setGeometry(QRect(20, 200, 113, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 120, 241, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 180, 211, 16));
        StartButton = new QPushButton(centralWidget);
        StartButton->setObjectName(QStringLiteral("StartButton"));
        StartButton->setGeometry(QRect(30, 20, 80, 23));
        ExitButton = new QPushButton(centralWidget);
        ExitButton->setObjectName(QStringLiteral("ExitButton"));
        ExitButton->setGeometry(QRect(30, 310, 80, 23));
        gv = new QGraphicsView(centralWidget);
        gv->setObjectName(QStringLiteral("gv"));
        gv->setGeometry(QRect(320, 10, 381, 341));
        p1score = new QLabel(centralWidget);
        p1score->setObjectName(QStringLiteral("p1score"));
        p1score->setGeometry(QRect(380, 380, 121, 20));
        p2score = new QLabel(centralWidget);
        p2score->setObjectName(QStringLiteral("p2score"));
        p2score->setGeometry(QRect(570, 380, 111, 17));
        rows = new QLabel(centralWidget);
        rows->setObjectName(QStringLiteral("rows"));
        rows->setGeometry(QRect(280, 20, 21, 31));
        cols = new QLabel(centralWidget);
        cols->setObjectName(QStringLiteral("cols"));
        cols->setGeometry(QRect(320, 350, 381, 20));
        rows_2 = new QLabel(centralWidget);
        rows_2->setObjectName(QStringLiteral("rows_2"));
        rows_2->setGeometry(QRect(280, 60, 21, 31));
        rows_3 = new QLabel(centralWidget);
        rows_3->setObjectName(QStringLiteral("rows_3"));
        rows_3->setGeometry(QRect(280, 100, 21, 31));
        rows_5 = new QLabel(centralWidget);
        rows_5->setObjectName(QStringLiteral("rows_5"));
        rows_5->setGeometry(QRect(280, 140, 21, 31));
        rows_6 = new QLabel(centralWidget);
        rows_6->setObjectName(QStringLiteral("rows_6"));
        rows_6->setGeometry(QRect(280, 180, 21, 31));
        rows_7 = new QLabel(centralWidget);
        rows_7->setObjectName(QStringLiteral("rows_7"));
        rows_7->setGeometry(QRect(280, 220, 21, 31));
        rows_8 = new QLabel(centralWidget);
        rows_8->setObjectName(QStringLiteral("rows_8"));
        rows_8->setGeometry(QRect(280, 260, 21, 31));
        rows_9 = new QLabel(centralWidget);
        rows_9->setObjectName(QStringLiteral("rows_9"));
        rows_9->setGeometry(QRect(280, 300, 21, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 725, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        SendButton->setText(QApplication::translate("MainWindow", "Send", 0));
        label->setText(QApplication::translate("MainWindow", "Piece to move (e.g. 0A)", 0));
        label_2->setText(QApplication::translate("MainWindow", "Position to move to (e.g. 1B)", 0));
        StartButton->setText(QApplication::translate("MainWindow", "Start Game", 0));
        ExitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
        p1score->setText(QApplication::translate("MainWindow", "P1:", 0));
        p2score->setText(QApplication::translate("MainWindow", "P2:", 0));
        rows->setText(QApplication::translate("MainWindow", "0", 0));
        cols->setText(QApplication::translate("MainWindow", "              A         B         C         D         E         F         G         H ", 0));
        rows_2->setText(QApplication::translate("MainWindow", "1", 0));
        rows_3->setText(QApplication::translate("MainWindow", "2", 0));
        rows_5->setText(QApplication::translate("MainWindow", "3", 0));
        rows_6->setText(QApplication::translate("MainWindow", "4", 0));
        rows_7->setText(QApplication::translate("MainWindow", "5", 0));
        rows_8->setText(QApplication::translate("MainWindow", "6", 0));
        rows_9->setText(QApplication::translate("MainWindow", "7", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
