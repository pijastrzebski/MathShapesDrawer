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

    void Init();
    QPointF compute( qreal typeOfShape);
protected:
    void paintEvent(QPaintEvent *event) override;
    void drawAstroid();
    void setColorsForPainter(QPainter& painter);

private:
    void on_shape_changed();

    QPointF computeAstroid(qreal step) const;
    QPointF computeCycloid(qreal step) const;
    QPointF computeHuygensCicloid(qreal step) const;
    QPointF computeHypoCycloid(qreal step) const;

    QPointF computeFutureCurve(qreal step) const;


private:
    QColor m_backgroundColor;
    QColor m_shapeColor;
    EShapes m_shape;

    qreal m_intervalLength;
    qreal m_scale;
    int m_stepCount;

signals:

public slots:
};

#endif // RENDERAREA_H
