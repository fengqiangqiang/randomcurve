#include "randomcurve.h"
#include <QtCore/QTime>
#include <QPainter>
#include <QtCore/QTime>

#include <QDebug>

RandomCurve::RandomCurve(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{}

void RandomCurve::componentComplete() {

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    int count = 40;
    int sw = width(); // 画布宽度
    int sh = height(); // 画布高度
    int pdia = 3; // 点圆直径
    int offset = pdia / 2;
    int oldpx = 0;
    int oldpy = 0;
    int px = qrand() % sw;
    int py = qrand() % sh;
    m_curvePath.moveTo(px, py);
    m_pointPath.addEllipse(px - offset, py - offset, pdia, pdia);
    oldpx = px;
    oldpy = py;
    for (int i = 0; i < count - 1; ++i) {
        px = qrand() % sw;
        py = qrand() % sh;
        m_pointPath.addEllipse(px - offset, py - offset, pdia, pdia);
        QPoint newp(px, py);
        QPoint oldp(oldpx, oldpy);
        QLineF otonv(oldp, newp);
        QLineF ntoov(newp, oldp);
        qreal angle = otonv.angle();

        QLineF rol1 = otonv;
        rol1.setAngle(angle + 90);
        rol1.setLength(otonv.length() / 4);
        QLineF rol2 = ntoov;
        rol2.setAngle(ntoov.angle() - 90);
        rol2.setLength(otonv.length() / 4);
        m_curvePath.cubicTo(rol1.p2(), rol2.p2(), newp);

        oldpx = px;
        oldpy = py;

    }
    QQuickPaintedItem::componentComplete();
}

void RandomCurve::paint(QPainter *painter)
{
    painter->setPen(Qt::green);
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawPath(m_curvePath);
    painter->setBrush(QBrush(Qt::green));
    painter->drawPath(m_pointPath);
}
