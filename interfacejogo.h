#ifndef INTERFACEJOGO_H
#define INTERFACEJOGO_H

#include <QWidget>
#include <QSizePolicy>
#include "peca.h"
#include <QSignalMapper>
#include <QElapsedTimer>

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

    QSignalMapper *m;
    QElapsedTimer qTimer;

private:
    Ui::InterfaceJogo *ui;
};

#endif // INTERFACEJOGO_H
