#include "peca.h"

Peca::Peca() {

}


Peca::Peca(int x, int y, int value)
{
    this->x = x;
    this->y = y;
    this->value = value;
    this->mapped = value;

    if (QString::compare(QString::number(value), QString::number(0)) == 0) {
        this->setText(" ");
    } else {
        this->setText(QString::number(value));
    }


    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Peca::changeText(QString newValue) {
    this->setText(newValue);
}

int Peca::getMapped() {
    return this->mapped;
}

int Peca::getX() {
    return this->x;
}

int Peca::getY() {
    return this->y;
}
