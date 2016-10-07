#include "interfacejogo.h"
#include "ui_interfacejogo.h"
#include "peca.h"
#include "jogo.h"
#include <iostream>
#include <QMessageBox>

InterfaceJogo::InterfaceJogo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterfaceJogo)
{
    ui->setupUi(this);
    this->m = new QSignalMapper(this);

    Jogo *jogo = new Jogo;
    jogo->setSignalMapper(this->m);
    jogo->setInterface(this);


    jogo->randomize();
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

    QString formattedStr = QString("VENCEDOR em %1 movimentos com tempo de %2 segundos")
            .arg(QString::number(moves), QString::number(time/1000));


    QMessageBox *dialog = new QMessageBox;
    dialog->setText(formattedStr);
    dialog->show();

    this->qTimer.restart();


}
