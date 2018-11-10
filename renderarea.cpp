#include "renderarea.h"

#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    m_backgroundColor(QColor(0, 0, 255)),
    m_shapeColor (255, 255, 255),
    m_shape(Astroid),
    m_cusp(2)
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

void RenderArea::resetCuspForNewShape(const EShapes &shape)
{
    if (m_shape == shape)
    {
        m_cusp++;
    }
    else
    {
        m_cusp = 2;
    }
}

RenderArea* RenderArea::setShape(const EShapes &shape)
{
    resetCuspForNewShape(shape);
    m_shape = shape;
    setupCurrentShape();
    return this;
}

void RenderArea::Init()
{
    setupCurrentShape();
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // removes warning
    drawShape();
}

void RenderArea::setColorsForPainter(QPainter& painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(m_backgroundColor);
    painter.setPen(m_shapeColor);
}

QPointF RenderArea::computeDispatcher( qreal theta)
{
    switch (m_shape)
    {
    case EShapes::Astroid:
        return computeAstroid(theta);
    case EShapes::Cycloid:
        return computeCycloid(theta);
   case EShapes::HuygensCycloid:
        return computeHuygens(theta);
   case EShapes::HypoCycloid:
        return computeHypo(theta);
    case EShapes::FutureCurve:
        return computeFutureCurve(theta);
    }

    return {0,0};
}

void RenderArea::drawShape()
{
    QPainter m_painter(this);

    setColorsForPainter(m_painter);
    m_painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    qreal theta = m_intervalLength / m_stepCount;

    for (qreal t = 0; t < m_intervalLength; t += theta)
    {
        QPointF point = computeDispatcher(t);

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

QPointF RenderArea::computeAstroid(qreal theta) const
{
    auto r = 2;
    auto cos_t = qCos(theta);
    auto sin_t = qSin(theta);
    auto x = r * qPow(cos_t, m_cusp);
    auto y = r * qPow(sin_t, m_cusp);

    return {x, y};
}

QPointF RenderArea::computeHuygens(qreal theta) const
{
    auto r = 4;
    auto x = r * (m_cusp * qCos(theta) - qCos(m_cusp * theta));
    auto y = r * (m_cusp * qSin(theta) - qSin(m_cusp * theta));

    return {x, y};
}

QPointF RenderArea::computeCycloid(qreal theta) const
{
    auto x = m_cusp * (theta - qSin(theta));
    auto y = m_cusp * (1 - qCos(theta));


    return {x, y};
}

QPointF RenderArea::computeHypo(qreal theta) const
{
    auto r = 1.5;
    auto x = r * ((m_cusp-1) * qCos(theta) + r * qCos((m_cusp-1) * theta));
    auto y = r * ((m_cusp-1) * qSin(theta) - r * qSin((m_cusp-1) * theta));

    return {x, y};
}

QPointF RenderArea::computeFutureCurve(qreal theta) const
{
    Q_UNUSED(theta); //TODO: impl
    return {0, 0};
}

void RenderArea::setupCurrentShape()
{
    switch(m_shape)
    {
        case EShapes::Astroid:
            m_scale = 40;
            m_intervalLength = static_cast<qreal>(2 * M_PI);
            m_stepCount = 256;
            break;
        case EShapes::HuygensCycloid:
            m_scale = 4;
            m_intervalLength = static_cast<qreal>(4 * M_PI);
            m_stepCount = 256;
            break;
        case EShapes::Cycloid:
            m_scale = 4;
            m_intervalLength = static_cast<qreal>(6 * M_PI);
            m_stepCount = 128;
            break;
        case EShapes::HypoCycloid:
            m_scale = 7;
            m_intervalLength = static_cast<qreal>(2 * M_PI);
            m_stepCount = 256;
            break;
        case EShapes::FutureCurve:

            break;
    }
}


