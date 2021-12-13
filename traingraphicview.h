#ifndef TRAINGRAPHICVIEW_H
#define TRAINGRAPHICVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>


class TrainGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    TrainGraphicsView(QWidget *parent);

private:
    QGraphicsScene *scene;
    QGraphicsTextItem *number;
};

#endif // TRAINGRAPHICVIEW_H
