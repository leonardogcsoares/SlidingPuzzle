#include "interfacejogo.h"
#include <QApplication>

/**
 * ################# TRABALHO PRÁTICO 1 - PAC ####################
 * ALUNOS: LUCAS GOULART GROSSI E LEONARDO GUALBERTO COELHO SOARES
 * ###############################################################
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceJogo w;
    w.show();

    return a.exec();
}
