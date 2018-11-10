#include "renderarea.h"

#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    m_backgroundColor(QColor(0, 0, 255)),
    m_shapeColor (255, 255, 255),
    m_shape(Astroid)
{

}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

RenderArea* RenderArea::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    return this;
}

RenderArea* RenderArea::setShape(const EShapes &shape)
{
    m_shape = shape;
    return this;
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // removes warning
    drawAstroid();
}

void RenderArea::setColorsForPainter(QPainter& painter)
{
    switch(m_shape)
    {
        case EShapes::Astroid:
            m_backgroundColor = Qt::GlobalColor::red;
            break;
        case EShapes::Cycloid:
            m_backgroundColor = Qt::GlobalColor::green;
            break;
        case EShapes::HuygensCicloid:
            m_backgroundColor = Qt::GlobalColor::blue;
            break;
        case EShapes::HypoCycloid:
            m_backgroundColor = Qt::GlobalColor::yellow;
            break;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(m_backgroundColor);
    painter.setPen(m_shapeColor);
}

void RenderArea::drawAstroid()
{
    QPainter m_painter(this);

    setColorsForPainter(m_painter);

    // drawing area
    m_painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    int stepCount = 256;
    qreal scale = 40;
    qreal intervalLength = static_cast<qreal>(2 * M_PI);
    qreal step = intervalLength / stepCount;

    for (qreal t = 0; t < intervalLength; t += step)
    {
        QPointF point = compute_astroid (t);

        QPoint pixel;
        pixel.setX(static_cast<int>(point.x() *
                   scale +
                   center.x()));

        pixel.setY(static_cast<int>(point.y() *
                   scale +
                   center.y()));

        m_painter.drawPoint(pixel);
    }

}

QPointF RenderArea::compute_astroid(qreal step) const
{
    auto cos_t = qCos(step);
    auto sin_t = qSin(step);
    auto x = 2 * qPow(cos_t, 3);
    auto y = 2 * qPow(sin_t, 3);

    return QPointF(x, y);
}


