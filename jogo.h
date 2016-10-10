#ifndef JOGO_H
#define JOGO_H

#include <QObject>
#include "time.h"
#include <QPushButton>
#include "interfacejogo.h"
#include "peca.h"
#include <QSignalMapper>

#define TAM 4

/**
 * ################# TRABALHO PRÁTICO 1 - PAC ####################
 * ALUNOS: LUCAS GOULART GROSSI E LEONARDO GUALBERTO COELHO SOARES
 * ###############################################################
*/

class Jogo : public QObject
{
    Q_OBJECT
public:
    explicit Jogo(QObject *parent = 0);

    int currentMatrix[TAM][TAM];
    Peca *buttonMatrix[TAM][TAM];

    InterfaceJogo *interface;
    QSignalMapper *m;


    void randomize();
    void setInterface(InterfaceJogo *interface);
    void setSignalMapper(QSignalMapper *m);
    void initMatrix();
    Peca* getPieceFromMap(int mapVal);
    bool isGameWon();
    int totalMoves();
    void newGame();


public slots:
    void piecePushed(int mapVal, bool randomizing=false);

private:
    int moves = 0;

    bool checkSolvable();
    void printMatrix();
    void addMove();
signals:

public slots:
};

#endif // JOGO_H
