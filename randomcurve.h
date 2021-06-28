#ifndef RANDOMCURVE_H
#define RANDOMCURVE_H

#include <QtQuick/QQuickPaintedItem>
#include <QPainterPath>

class RandomCurve : public QQuickPaintedItem{

    Q_OBJECT
public:
    RandomCurve(QQuickItem *parent = 0);


protected:
    void componentComplete();
    void paint(QPainter *painter);

private:
    QPainterPath m_pointPath;
    QPainterPath m_curvePath;
};

#endif // RANDOMCURVE_H
