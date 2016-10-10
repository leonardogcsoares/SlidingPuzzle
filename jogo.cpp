#include "jogo.h"
#include "interfacejogo.h"
#include <iostream>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <stdio.h>

/**
 * ################# TRABALHO PRÁTICO 1 - PAC ####################
 * ALUNOS: LUCAS GOULART GROSSI E LEONARDO GUALBERTO COELHO SOARES
 * ###############################################################
*/

/** Método que cria um delay. */
void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(300);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Jogo::Jogo(QObject *parent) : QObject(parent) {

}

/** Método que seta a interface.*/
void Jogo::setInterface(InterfaceJogo *interface)
{
    this->interface = interface;

    this->interface->printWorking();

    std::cout << "Jogo Constructor" << std::endl;
    // Initializes matrix with empty values initially
    for(int i=0; i < 4; ++i) {
        for(int j=0; j < 4; ++j) {
            this->currentMatrix[i][j] = 0;
        }
    }
}

/** Método que seta o signalmapper.*/
void Jogo::setSignalMapper(QSignalMapper *m) {
    this->m = m;
}

/** Método que inicializa a matriz de botões.*/
void Jogo::initMatrix() {
    for (int x=0; x < TAM; ++x) {
        for (int y=0; y < TAM; ++y) {
            Peca *piece = new Peca(x, y, TAM*x+y);

            connect(piece, SIGNAL(clicked()), this->m, SLOT(map()));
            this->m->setMapping(piece, piece->getMapped());

            this->buttonMatrix[x][y] = piece;
            this->interface->addPieceToGrid(piece, x, y);
        }
    }
    connect(m, SIGNAL(mapped(int)), this, SLOT(piecePushed(int)));
    std::cout << "Added pieces to grid" << std::endl;
    this->randomize();
}

/** Método que randomiza os valores da matriz.*/
void Jogo::randomize() {

    this-> moves = 0;
    srand(time(NULL));

    for (int x=0; x<TAM; ++x) {
        for (int y=0; y<TAM; ++y) {
            this->currentMatrix[x][y] = TAM*x+y;
        }
    }

    do {
        for (int x=0; x<TAM; ++x) {
            for (int y=0; y<TAM; ++y) {
                int temp = this->currentMatrix[x][y];
                int randomX = rand()%TAM;
                int randomY = rand()%TAM;

                this->currentMatrix[x][y] = this->currentMatrix[randomX][randomY];
                this->currentMatrix[randomX][randomY] = temp;
            }
        }
    } while(!this->checkSolvable());

        this->printMatrix();
        this->newGame();
}

/** Método que verifica se o puzzle tem solução. Retorna true em caso positivo e false em caso negativo.*/
bool Jogo::checkSolvable() {
    int inversions = 0;
    int blankSpaceRow = 0;
    QVector<int> integerVector;

    for(int x=0;x<TAM; ++x){
        for(int y=0;y<TAM;++y){
            if (this->currentMatrix[x][y] == 0) {
                blankSpaceRow = x+1;
            }
            integerVector.append(this->currentMatrix[x][y]);
        }
    }

    for(int x=0;x<integerVector.length(); ++x){
        for(int y=x+1;y<integerVector.length();++y){
            if(integerVector[y] > integerVector[x]){
                inversions++;
            }
        }
    }

    std::cout << blankSpaceRow << " " << inversions << std::endl;

    return blankSpaceRow % 2 == 1 ? (inversions%2 == 1 ? false : true) : (inversions%2 == 1 ? true : false);
}

/** Método que cria um novo jogo.*/
void Jogo::newGame() {
    for (int x=0; x < 4; ++x) {
        for (int y=0; y < 4; ++y) {
            this->buttonMatrix[x][y]->changeText(currentMatrix[x][y]);
        }
    }
}

/** Método move a peça quando clica nela.*/
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

/** Método que retorna uma peça no mapa. */
Peca* Jogo::getPieceFromMap(int mapVal) {
    for (int x=0; x < TAM; ++x) {
        for (int y=0; y < TAM; ++y) {
            if (mapVal == this->buttonMatrix[x][y]->getMapped()){
                return this->buttonMatrix[x][y];
            }
        }
    }
}

/** Método que incrementa o número de movimentos*/
void Jogo::addMove() {
    ++this->moves;
}

/** Método que retorna o total de movimentos feitos.*/
int Jogo::totalMoves() {
    return this->moves;
}

/** Método que verifica se o jogo foi ganho.*/
bool Jogo::isGameWon() {
    int c = 1;
    for (int x=0; x < TAM; ++x) {
        for (int y=0; y < TAM; ++y) {
            if (x==3 && y==3){
               break;
            }
            std::cout << "Desired: " << QString::number(c).toStdString() << " Button value: " << buttonMatrix[x][y]->text().toStdString() << std::endl;
            if (QString::compare(QString::number(c),buttonMatrix[x][y]->text())) {
                return false;
            }
            ++c;
        }
    }

    return true;
}

/** Método que printa a matriz de valores.*/
void Jogo::printMatrix() {
    std::cout << "printMatrix called" << std::endl;

    for(int i=0; i < TAM; ++i) {
        for(int j=0; j < TAM; ++j) {
            std::cout << this->currentMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


