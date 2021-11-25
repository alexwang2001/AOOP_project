#ifndef TRAINDPSCROLL_H
#define TRAINDPSCROLL_H

#include <QObject>
#include <QScrollArea>
#include <QVector>
#include "traindisp.h"

class TrainDPscroll: public QScrollArea
{
    Q_OBJECT
public:
    TrainDPscroll(QWidget *parent);


private:
    QVector<Traindisp*> traindisps;
};

#endif // TRAINDPSCROLL_H
