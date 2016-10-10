#include "interfacejogo.h"
#include "ui_interfacejogo.h"
#include "peca.h"
#include "jogo.h"
#include <iostream>
#include <QMessageBox>

/**
 * ################# TRABALHO PRÁTICO 1 - PAC ####################
 * ALUNOS: LUCAS GOULART GROSSI E LEONARDO GUALBERTO COELHO SOARES
 * ###############################################################
*/

InterfaceJogo::InterfaceJogo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterfaceJogo)
{
    load();
    ui->setupUi(this);
    this->m = new QSignalMapper(this);

    Jogo *jogo = new Jogo;
    jogo->setSignalMapper(this->m);
    jogo->setInterface(this);

    jogo->initMatrix();
    this->qTimer.start();
}

InterfaceJogo::~InterfaceJogo()
{
    delete ui;
}

void InterfaceJogo::printWorking() {
    std::cout << "Interface call from Jogo class" << std::endl;
}

void InterfaceJogo::addPieceToGrid(Peca *piece, int x, int y) {
    ui->gridLayout->addWidget(piece, x, y);
}

void InterfaceJogo::switchPieces(Peca *p1, Peca *p2) {
    QString tmp = p1->text();
    p1->setText(p2->text());
    p2->setText(tmp);
}

void InterfaceJogo::gameWon(int moves){
    int time = this->qTimer.elapsed();

    QString formattedStr = QString("VENCEDOR em %1 movimentos com tempo de %2 segundos\n")
            .arg(QString::number(moves), QString::number(time/1000));

    save(moves, time/1000);

    if (records[0][0] != -1) {
        formattedStr.insert(formattedStr.size(),"\nHall da fama:\n");

        for (int i = 0; i < MAX_RECORDS; ++i){
            if (records[i][0] == -1) break;
            formattedStr.insert(formattedStr.size(), QString("%1. %2 movimentos - %3 segundos\n").arg(i+1).arg(records[i][0]).arg(records[i][1]));
        }
    }

    QMessageBox *dialog = new QMessageBox;
    dialog->setText(formattedStr);
    dialog->show();

    for (int i = 0; i < MAX_RECORDS; ++i){
        std::cout << this->records[i][0] << ' ' << this->records[i][1] << std::endl;
    }

    this->qTimer.restart();
}


/** Método que salva o hall of fame. */
void InterfaceJogo::save(int moves, int time) {
    FILE * pFile;
    pFile = fopen ("halloffame.txt","w");
    int aux = 0;
    if (pFile==NULL) perror ("Error opening file");
    else
    {
      for (int i = 0; i < MAX_RECORDS; ++i) {
          bool empty = false;
          if (this->records[i][0] == -1) {
              this->records[i][0] = moves;
              this->records[i][1] = time;
              empty = true;
          }
          if (moves < this->records[i][0]) {
              aux = moves;
              moves = this->records[i][0];
              this->records[i][0] = aux;
          }
          if (time < this->records[i][1]) {
              aux = time;
              time = this->records[i][1];
              this->records[i][1] = aux;
          }

          QString formattedStr = QString("%1,%2\n")
                  .arg(this->records[i][0]).arg(this->records[i][1]);
          fputs (formattedStr.toLatin1().data(), pFile);

          if(empty) break;
      }
      fclose (pFile);
    }
}

/** Método que carrega o hall of fame. */
void InterfaceJogo::load() {
    for (int i = 0; i < MAX_RECORDS; ++ i) {
        this->records[i][0] = -1;
        this->records[i][1] = -1;
    }
    FILE * pFile;
    pFile = fopen ("halloffame.txt","r");
    if (pFile==NULL) perror ("Error opening file");
    else
    {
        if (!feof(pFile)) {
            for (int i = 0; i < MAX_RECORDS; ++ i) {
                char line[MAX_RECORDS];
                fgets(line, 10, pFile);
                if (line != NULL) {
                    QString str(line);
                    QStringList strList = str.split(',');
                    if (strList.size() == 2) {
                        this->records[i][0] = strList[0].toInt();
                        this->records[i][1] = strList[1].toInt();
                    }
                }
                if (feof(pFile)) break;
            }
        }
      fclose (pFile);
    }
}
