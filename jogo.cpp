#include "jogo.h"
#include "interfacejogo.h"
#include <iostream>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(300);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Jogo::Jogo(QObject *parent) : QObject(parent) {

}

void Jogo::setInterface(InterfaceJogo *interface)
{
    this->interface = interface;

    this->interface->printWorking();

    std::cout << "Jogo Constructor" << std::endl;
    // Initializes matrix with empty values initially
    for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
            this->currentMatrix[i][j] = 0;
        }
    }
}

void Jogo::setSignalMapper(QSignalMapper *m) {
    this->m = m;
}

void Jogo::randomize() {

    srand(time(NULL));

//    for (int i=1; i <= 15; i++) {
//        int x = rand()%4;
//        int y = rand()%4;
//        while(1) {
//            if (this->currentMatrix[x][y] == 0) {
//                this->currentMatrix[x][y] = i;
//                break;
//            }
//            x = rand()%4;
//            y = rand()%4;
//        }
//    }


    // One piece to win (FOR TESTING WIN CONDITION)
    int count = 1;
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            if (x==3 && y==2 ){
                break;
            }
            this->currentMatrix[x][y] = count;
            count++;
        }
    }
    this->currentMatrix[3][3] = 15;



    this->printMatrix();
    this->newGame();
}

void Jogo::newGame() {
    for (int x=0; x < 4; x++) {
        for (int y=0; y < 4; y++) {
            Peca *piece = new Peca(x, y, this->currentMatrix[x][y]);

            connect(piece, SIGNAL(clicked()), this->m, SLOT(map()));
            this->m->setMapping(piece, piece->getMapped());



            this->buttonMatrix[x][y] = piece;
            this->interface->addPieceToGrid(piece, x, y);
        }
    }

    connect(m, SIGNAL(mapped(int)), this, SLOT(piecePushed(int)));

    std::cout << "Added pieces to grid" << std::endl;
}

void Jogo::piecePushed(int mapVal) {


    Peca *piece = this->getPieceFromMap(mapVal);
    std::cout << "Piece pushed: " << piece->getX() << ", " << piece->getY() << std::endl;

    int x = piece->getX();
    int y = piece->getY();

    Peca *pieceToSwitch;
    bool switchFound = false;

    Peca *checkPiece;
    // Check north
    if (x > 0) {
        checkPiece= this->buttonMatrix[x-1][y];
        std::cout << "Check piece: " << checkPiece->getX() << ", " << checkPiece->getY() << std::endl;
        if (checkPiece->text() == " ") {
            std::cout << "North empty" << std::endl;
            switchFound = true;
            pieceToSwitch = checkPiece;
        }
    // Check south
    }
    if (x < 3 && !switchFound) {
        checkPiece = this->buttonMatrix[x+1][y];
        std::cout << "Check piece: " << checkPiece->getX() << ", " << checkPiece->getY() << std::endl;
        if (checkPiece->text() == " ") {
            std::cout << "South empty" << std::endl;
            switchFound = true;
            pieceToSwitch = checkPiece;
        }
    }
    // Check west
    if (y > 0 && !switchFound) {
        checkPiece = this->buttonMatrix[x][y-1];
        std::cout << "Check piece: " << checkPiece->getX() << ", " << checkPiece->getY() << std::endl;
        if (checkPiece->text() == " ") {
            std::cout << "West empty" << std::endl;
            switchFound = true;
            pieceToSwitch = checkPiece;
        }
    }
    // Check east
    if (y < 3 && !switchFound) {
        checkPiece = this->buttonMatrix[x][y+1];
        std::cout << "Check piece: " << checkPiece->getX() << ", " << checkPiece->getY() << std::endl;
        if (checkPiece->text() == " ") {
            std::cout << "East empty" << std::endl;
            switchFound = true;
            pieceToSwitch = checkPiece;
        }
    }

    if (switchFound) {
        interface->switchPieces(piece, pieceToSwitch);

        this->addMove();
        if (this->isGameWon()) {
            delay();
            this->interface->gameWon(this->moves);
            this->randomize();
        }
    }
}

Peca* Jogo::getPieceFromMap(int mapVal) {
    for (int x=0; x < 4; x++) {
        for (int y=0; y < 4; y++) {
            if (mapVal == this->buttonMatrix[x][y]->getMapped()){
                return this->buttonMatrix[x][y];
            }
        }
    }
}

void Jogo::addMove() {
    this->moves++;
}

int Jogo::totalMoves() {
    return this->moves;
}

bool Jogo::isGameWon() {
    int c = 1;
    for (int x=0; x < 4; x++) {
        for (int y=0; y < 4; y++) {
            if (x==3 && y==3){
               break;
            }

            std::cout << "Desired: " << QString::number(c).toStdString() << " Button value: " << buttonMatrix[x][y]->text().toStdString() << std::endl;
            if (QString::compare(QString::number(c),buttonMatrix[x][y]->text())) {
                return false;
            }
            c++;
        }
    }

    return true;
}

void Jogo::printMatrix() {
    std::cout << "printMatrix called" << std::endl;

    for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
            std::cout << this->currentMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


