#ifndef JOGO_H
#define JOGO_H

#include <QObject>

class Jogo : public QObject
{
    Q_OBJECT
public:
    explicit Jogo(QObject *parent = 0);

signals:

public slots:
};

#endif // JOGO_H