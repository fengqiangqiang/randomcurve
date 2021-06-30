#ifndef RANDOMCURVE_H
#define RANDOMCURVE_H

#include <QtQuick/QQuickPaintedItem>
#include <QPainterPath>

class QTimer;
class RandomCurve : public QQuickPaintedItem {

    Q_OBJECT
public:
    RandomCurve(QQuickItem *parent = 0);

public Q_SLOTS:
    void buildCurve();

protected:
    void paint(QPainter *painter);
    void componentComplete();

private:
    QPainterPath m_pointPath;
    QPainterPath m_curvePath;
    QTimer* m_buildCurveTimer;
    int m_pointCount;
    int m_oldpx;
    int m_oldpy;
    int m_sw;  // 画布宽度
    int m_sh;  // 画布高度
    int m_pdia; // 点圆直径
    int m_offset;
};

#endif // RANDOMCURVE_H
