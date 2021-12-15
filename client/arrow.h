#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsItem>
#include <QBrush>
#include <QPainterPath>
#include <QVector>
#include <QPointF>
#include <QPainter>

class Arrow : public QGraphicsItem
{
public:
    Arrow();

    QRectF boundingRect() const{
        return path.boundingRect();
    }

    QPainterPath shape() const{
        return path;
    }

    virtual void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ){
        painter->fillPath(path,brush);
    }

protected:
    QBrush brush;
    QPainterPath path;
};

#endif // ARROW_H
