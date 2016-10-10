#ifndef INTERFACEJOGO_H
#define INTERFACEJOGO_H

#include <QWidget>
#include <QSizePolicy>
#include "peca.h"
#include <QSignalMapper>
#include <QElapsedTimer>

#define MAX_RECORDS 10

/**
 * ################# TRABALHO PRÁTICO 1 - PAC ####################
 * ALUNOS: LUCAS GOULART GROSSI E LEONARDO GUALBERTO COELHO SOARES
 * ###############################################################
*/

namespace Ui {
class InterfaceJogo;
}

class InterfaceJogo : public QWidget
{
    Q_OBJECT

public:
    explicit InterfaceJogo(QWidget *parent = 0);
    ~InterfaceJogo();

    void printWorking();
    void addPieceToGrid(Peca *piece, int x, int y);
    void switchPieces(Peca *p1, Peca *p2);
    void gameWon(int moves);
    void save(int moves, int time);
    void load();

    int records[MAX_RECORDS][2];
    QSignalMapper *m;
    QElapsedTimer qTimer;

private:
    Ui::InterfaceJogo *ui;
};

#endif // INTERFACEJOGO_H
