#include "arrow.h"

Arrow::Arrow(){
    brush.setColor( QColor::fromRgb(255,165,0));
    brush.setStyle(Qt::SolidPattern);

    QVector<QPointF> vec;

    vec.push_back(QPointF(-15,-3));
    vec.push_back(QPointF(28,-3));
    vec.push_back(QPointF(10,8));
    vec.push_back(QPointF(10,3));
    vec.push_back(QPointF(-15,3));

    path.addPolygon(QPolygonF(vec));

}
