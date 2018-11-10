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
    Init();
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
    on_shape_changed();
    return this;
}

void RenderArea::Init()
{
    on_shape_changed();
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // removes warning
    drawAstroid();
}

void RenderArea::setColorsForPainter(QPainter& painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(m_backgroundColor);
    painter.setPen(m_shapeColor);
}

QPointF RenderArea::compute( qreal typeOfShape)
{
    switch (m_shape)
    {
    case EShapes::Astroid:
        return computeAstroid(typeOfShape);
        break;
    case EShapes::Cycloid:
        return computeCycloid(typeOfShape);
        break;
    case EShapes::HuygensCicloid:
        return computeHuygensCicloid(typeOfShape);
        break;
    case EShapes::HypoCycloid:
        return computeHypoCycloid(typeOfShape);
        break;
    case EShapes::FutureCurve:
        return computeFutureCurve(typeOfShape);
        break;
    }

    return {0,0};
}

void RenderArea::drawAstroid()
{
    QPainter m_painter(this);

    setColorsForPainter(m_painter);

    // drawing area
    m_painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    qreal step = m_intervalLength / m_stepCount;

    for (qreal t = 0; t < m_intervalLength; t += step)
    {
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(static_cast<int>(point.x() *
                   m_scale +
                   center.x()));

        pixel.setY(static_cast<int>(point.y() *
                   m_scale +
                   center.y()));

        m_painter.drawPoint(pixel);
    }

}

QPointF RenderArea::computeAstroid(qreal step) const
{
    auto cos_t = qCos(step);
    auto sin_t = qSin(step);
    auto x = 2 * qPow(cos_t, 3);
    auto y = 2 * qPow(sin_t, 3);

    return QPointF(x, y);
}

QPointF RenderArea::computeCycloid(qreal step) const
{
    return {0, 0};
}

QPointF RenderArea::computeHuygensCicloid(qreal step) const
{
    return {0, 0};
}

QPointF RenderArea::computeHypoCycloid(qreal step) const
{
    return {0, 0};
}

QPointF RenderArea::computeFutureCurve(qreal step) const
{
    return {0, 0};
}

void RenderArea::on_shape_changed()
{
    switch(m_shape)
    {
        case EShapes::Astroid:
            m_scale = 40;
            m_intervalLength = static_cast<qreal>(2 * M_PI);
            m_stepCount = 256;
            break;
        case EShapes::Cycloid:

            break;
        case EShapes::HuygensCicloid:

            break;
        case EShapes::HypoCycloid:

            break;
        case EShapes::FutureCurve:

            break;
    }
}


