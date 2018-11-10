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

    RenderArea* incrementCusp() { m_cusp++; return this;}

    void Init();
    QPointF computeDispatcher( qreal typeOfShape);

    void resetCuspForNewShape(const EShapes &shape);

protected:
    void paintEvent(QPaintEvent *event) override;
    void drawShape();
    void setColorsForPainter(QPainter& painter);

private:
    void setupCurrentShape();

    QPointF computeAstroid(qreal step) const;
    QPointF computeCycloid(qreal step) const;
    QPointF computeHuygens(qreal step) const;
    QPointF computeHypo(qreal step) const;

    QPointF computeFutureCurve(qreal step) const;


private:
    QColor m_backgroundColor;
    QColor m_shapeColor;
    EShapes m_shape;

    qreal m_intervalLength;
    qreal m_scale;
    int m_stepCount;
    int m_cusp;

signals:

public slots:
};

#endif // RENDERAREA_H
