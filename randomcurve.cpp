#include "randomcurve.h"
#include <QtCore/QTime>
#include <QPainter>
#include <QTime>
#include <QTimer>

#include <QDebug>

RandomCurve::RandomCurve(QQuickItem *parent)
    :QQuickPaintedItem(parent),
      m_pointCount(10000),
      m_oldpx(0),
      m_oldpy(0),
      m_pdia(3) {

    m_offset = m_pdia / 2;

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    m_buildCurveTimer = new QTimer(this);
    m_buildCurveTimer->setInterval(100);
    connect(m_buildCurveTimer, SIGNAL(timeout()), this, SLOT(buildCurve()));
    m_buildCurveTimer->start();
}

void RandomCurve::componentComplete() {

    m_sw = width(); // 画布宽度
    m_sh = height(); // 画布高度
    int px = qrand() % m_sw;
    int py = qrand() % m_sh;
    m_curvePath.moveTo(px, py);
    QQuickPaintedItem::componentComplete();
}


void RandomCurve::buildCurve() {

    static int alreadyDrawCount = 0;
    if (alreadyDrawCount >= m_pointCount) {
        m_buildCurveTimer->stop();
        return;
    }

    if(!(alreadyDrawCount % 20)) {
        m_curvePath = QPainterPath();
        m_curvePath.moveTo(m_oldpx, m_oldpy);
        m_pointPath = QPainterPath();
    }

    int px = qrand() % m_sw;
    int py = qrand() % m_sh;

    m_pointPath.addEllipse(px - m_offset, py - m_offset, m_pdia, m_pdia);

    QPoint newp(px, py);
    QPoint oldp(m_oldpx, m_oldpy);
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

    m_oldpx = px;
    m_oldpy = py;

    alreadyDrawCount += 1;

    update();
}

void RandomCurve::paint(QPainter *painter) {

    painter->setPen(Qt::green);
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawPath(m_curvePath);
    painter->setBrush(QBrush(Qt::green));
    painter->drawPath(m_pointPath);
}

