#ifndef JOGO_H
#define JOGO_H

#include <QObject>
#include "time.h"
#include <QPushButton>
#include "interfacejogo.h"
#include "peca.h"
#include <QSignalMapper>


class Jogo : public QObject
{
    Q_OBJECT
public:
    explicit Jogo(QObject *parent = 0);


    int currentMatrix[4][4];
    Peca *buttonMatrix[4][4];

    InterfaceJogo *interface;
    QSignalMapper *m;


    void randomize();
    void setInterface(InterfaceJogo *interface);
    void setSignalMapper(QSignalMapper *m);
    Peca* getPieceFromMap(int mapVal);
    bool isGameWon();
    int totalMoves();
    void newGame();


public slots:
    void piecePushed(int mapVal);

private:
    int moves = 0;

    void printMatrix();
    void addMove();
signals:

public slots:
};

#endif // JOGO_H
