/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(684, 419);
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
        label_2->setGeometry(QRect(20, 180, 291, 16));
        StartButton = new QPushButton(centralWidget);
        StartButton->setObjectName(QStringLiteral("StartButton"));
        StartButton->setGeometry(QRect(30, 20, 80, 23));
        ExitButton = new QPushButton(centralWidget);
        ExitButton->setObjectName(QStringLiteral("ExitButton"));
        ExitButton->setGeometry(QRect(30, 310, 80, 23));
        gv = new QGraphicsView(centralWidget);
        gv->setObjectName(QStringLiteral("gv"));
        gv->setGeometry(QRect(290, 1, 381, 341));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 684, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        SendButton->setText(QApplication::translate("MainWindow", "Send", 0));
        label->setText(QApplication::translate("MainWindow", "Select Piece to move (e.g. 0A)", 0));
        label_2->setText(QApplication::translate("MainWindow", "Select the position to move to (e.g. 1B)", 0));
        StartButton->setText(QApplication::translate("MainWindow", "Start Game", 0));
        ExitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
