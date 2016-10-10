#ifndef PECA_H
#define PECA_H

#include <QObject>
#include <QPushButton>
#include <QString>
#include <QSizePolicy>

/**
 * ################# TRABALHO PRÁTICO 1 - PAC ####################
 * ALUNOS: LUCAS GOULART GROSSI E LEONARDO GUALBERTO COELHO SOARES
 * ###############################################################
*/

class Peca : public QPushButton
{
private:
    int x, y;
    int mapped;


public:
    int value;

    Peca();
    Peca(int x, int y, int value);
    void changeText(int newValue);
    void changeText(QString newValue);
    int getMapped();
    int getX();
    int getY();
};

#endif // PECA_H
