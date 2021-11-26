#include "mygraphicview.h"

TrainGraphicsView::TrainGraphicsView(QWidget *parent): QGraphicsView(parent){
    scene = new QGraphicsScene(0,0,300,100);
    this->setScene(scene);
    this->setContentsMargins(0,0,0,0);
    number = new QGraphicsTextItem("hi");
    number->setPos(10,10);
    scene->addItem(number);
}
