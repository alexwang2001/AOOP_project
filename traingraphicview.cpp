#include "traingraphicview.h"

TrainGraphicsView::TrainGraphicsView(QWidget *parent): QGraphicsView(parent){

    mx = 0;
    my = 0;
}

TrainGraphicsView::~TrainGraphicsView(){

    /*delete trainNumber;
    delete depStr;
    delete arrStr;
    delete deptStr;
    delete arrtStr;
    delete arrow;
    delete button;
    delete button_txt;*/

    scene->deleteLater();
}

void TrainGraphicsView::TrainInquryView(int trainNum, CQstrRef dep, CQstrRef termi, int dep_time, int arr_time){
    scene = new QGraphicsScene(0,0,300,100);
    this->setScene(scene);
    this->setContentsMargins(0,0,0,0);


    this->trainNum = trainNum;
    this->dep = dep;
    this->termi = termi;
    this->dep_time = dep_time;
    this->arr_time = arr_time;


    trainNumber = new QGraphicsTextItem("TrainNO "+ QString::number(trainNum));
    trainNumber->setPos(-30,0);
    scene->addItem(trainNumber);

    depStr = new QGraphicsTextItem(dep);
    depStr->setPos(80,40);
    scene->addItem(depStr);

    arrStr = new QGraphicsTextItem(termi);
    arrStr->setPos(180,40);
    scene->addItem(arrStr);

    deptStr = new QGraphicsTextItem(QString::number(dep_time));
    deptStr->setPos(80,60);
    scene->addItem(deptStr);

    arrtStr = new QGraphicsTextItem(QString::number(arr_time));
    arrtStr->setPos(180,60);
    scene->addItem(arrtStr);

    //arrow = new Arrow;
    //arrow->setPos(145,60);
    //scene->addItem(arrow);

    button = new QGraphicsRectItem;
    QBrush brush;
    brush.setColor( QColor::fromRgb(244, 220, 145));
    brush.setStyle(Qt::SolidPattern);
    button->setBoundingRegionGranularity(0);
    button->setBrush(brush);
    button->setRect(280,80,50,20);
    scene->addItem(button);

    button_txt = new QGraphicsTextItem("Book");
    button_txt->setFont(QFont("Arial",10));
    button_txt->setDefaultTextColor(QColor::fromRgb(242, 140, 71));
    button_txt->setPos(285,80);
    scene->addItem(button_txt);
}

void TrainGraphicsView::mousePressEvent(QMouseEvent *event){
    mx = event->pos().x();
    my = event->pos().y();
    qDebug() << "click event" << mx << my;
    if(mx > 320 && mx < 370 && my > 90 && my < 110){
        emit BuyTicketClicked();
        qDebug() << "clicked";
    }

}
