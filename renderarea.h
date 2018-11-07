#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

#include "eshapes.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    RenderArea* setBackgroundColor(const QColor& color);
    const QColor& getBackgroundColor() const {return m_backgroundColor;}

    RenderArea* setShape(const EShapes& shape);
    const EShapes& getShape() const {return m_shape;}
protected:
    void paintEvent(QPaintEvent *event) override;

    void drawRectangleWithLine();

    void setColorsForPainter(QPainter& painter);

private:
    QColor m_backgroundColor;
    QColor m_shapeColor;
    EShapes m_shape;

signals:

public slots:
};

#endif // RENDERAREA_H
