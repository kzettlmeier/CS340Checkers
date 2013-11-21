#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T21:56:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 340Checkers
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    game.cpp \
    ai.cpp \
    tile.cpp

HEADERS  += mainwindow.h \
    board.h \
    game.h \
    ai.h \
    tile.h

FORMS    += mainwindow.ui
