#include "renderarea.h"

#include <QPaintEvent>
#include <QPainter>
#include <QColor>

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
    Q_UNUSED(event);
    drawRectangleWithLine();
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

void RenderArea::drawRectangleWithLine()
{
    QPainter m_painter(this);

    setColorsForPainter(m_painter);

    // drawing area
    m_painter.drawRect(this->rect());
    m_painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
}


