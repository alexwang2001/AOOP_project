#ifndef TRAINGRAPHICVIEW_H
#define TRAINGRAPHICVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <arrow.h>

typedef const QString& CQstrRef;

class TrainGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    TrainGraphicsView(QWidget *parent);
    ~TrainGraphicsView();

    void TrainInquryView(int trainNum, CQstrRef dep, CQstrRef termi, int dep_time, int arr_time);

    int trainNum;
    QString dep;
    QString termi;
    int dep_time;
    int arr_time;

signals:
    void BuyTicketClicked();

private:
    QGraphicsScene *scene;
    QGraphicsTextItem *trainNumber;
    QGraphicsTextItem *depStr;
    QGraphicsTextItem *arrStr;
    QGraphicsTextItem *deptStr;
    QGraphicsTextItem *arrtStr;

    Arrow *arrow;
    QGraphicsRectItem *button;
    QGraphicsTextItem *button_txt;

    int mx, my;

private slots:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // TRAINGRAPHICVIEW_H
