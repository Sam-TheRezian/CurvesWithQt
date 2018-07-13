#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {
        Astroid, Cycloid, HuygensCycloid, HypoCycloid, FutureCurve
    };

    //Backgorund getter and setter
    void setBackground(QColor color) { mBackgroundColor = color; onShapeChanged();}
    QColor getBackground() const { return mBackgroundColor;}

    //Shape getter and setter
    void setShape(ShapeType shape) { mShape = shape; }
    ShapeType getShape() const { return mShape; }

    void setScale(double scale) { mScale = scale; repaint(); }
    double getScale() const { return mScale; }

    void setInterval(double interval) { mIntervalLength = interval; repaint(); }
    double getInterval() const { return mIntervalLength; }

    void setStepCount(int stepCount) { mStepCount = stepCount; repaint(); }
    int getStepCount() const { return mStepCount; }



private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;
    int mStepCount;
    float mScale;
    float mIntervalLength;

    QPointF compute(float t); //dispatch function for shape
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypocycloid(float t);
    QPointF compute_future_curve(float t);
    void onShapeChanged();


protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // RENDERAREA_H
