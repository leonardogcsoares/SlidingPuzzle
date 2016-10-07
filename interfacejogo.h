#ifndef INTERFACEJOGO_H
#define INTERFACEJOGO_H

#include <QWidget>

namespace Ui {
class InterfaceJogo;
}

class InterfaceJogo : public QWidget
{
    Q_OBJECT

public:
    explicit InterfaceJogo(QWidget *parent = 0);
    ~InterfaceJogo();

private:
    Ui::InterfaceJogo *ui;
};

#endif // INTERFACEJOGO_H
