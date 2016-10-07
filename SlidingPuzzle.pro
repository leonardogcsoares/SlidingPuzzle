#-------------------------------------------------
#
# Project created by QtCreator 2016-10-06T20:37:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SlidingPuzzle
TEMPLATE = app


SOURCES += main.cpp\
        interfacejogo.cpp \
    jogo.cpp \
    peca.cpp

HEADERS  += interfacejogo.h \
    jogo.h \
    peca.h

FORMS    += interfacejogo.ui
