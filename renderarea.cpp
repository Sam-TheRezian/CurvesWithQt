#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>
#include <math.h>
#include <QColor>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent),
    mBackgroundColor (255, 0, 0),
    mShapeColor (255, 255, 255),
    mShape (Astroid)
{
    this->setStyleSheet("background-color:blue;");
    onShapeChanged();
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

void RenderArea::onShapeChanged() {
    switch (mShape) {
    case Astroid:
        mStepCount = 256;
        RenderArea::mScale = 40;
        mIntervalLength = 2 * M_PI;
        break;
    case Cycloid:
        mStepCount = 128;
        RenderArea::mScale = 4;
        mIntervalLength = 6 * M_PI;
        break;
    case HuygensCycloid:
        mStepCount = 256;
        RenderArea::mScale = 4;
        mIntervalLength = 4 * M_PI;
        break;
    case HypoCycloid:
        mScale = 15;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case FutureCurve:
        mIntervalLength = 1;
        mScale = 50;
        mStepCount = 128;
        break;
    default:
        break;
    }
}

QPointF RenderArea::compute_astroid(float t) {
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * pow(cos_t, 3);
    float y = 2 * pow(sin_t, 3);
    return QPointF(x, y);
}

QPointF RenderArea::compute_cycloid(float t) {
    return QPointF(0.5 * (1 - cos(t)), 0.5 * (t - sin(t)));
}

QPointF RenderArea::compute_huygens(float t) {
    return QPointF(0.5 * (3*cos(t) - cos(3*t)), 0.5 * (3*sin(t) - sin(3*t)));
}

QPointF RenderArea::compute_hypocycloid(float t) {
    return QPointF(0.75 * (2*cos(t) + cos(2*t)), 0.75 * (2*sin(t) - sin(2*t)));
}

QPointF RenderArea::compute_future_curve(float t) {
    return QPointF(1 - t, 1 - t);
}

QPointF RenderArea::compute(float t) {
    switch (mShape) {
    case Astroid:
        return compute_astroid(t);
        break;
    case Cycloid:
        return compute_cycloid(t);
        break;
    case HuygensCycloid:
        return compute_huygens(t);
        break;
    case HypoCycloid:
        return compute_hypocycloid(t);
        break;
    case FutureCurve:
        return compute_future_curve(t);
        break;
    default:
        break;
    }
    return QPointF(0, 0);
}

void RenderArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    //draw area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();
    float step = mIntervalLength / mStepCount;
    for(float t = 0; t < mIntervalLength; t += step) {
        QPointF point = compute(t);
        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y()) ;

        painter.drawPoint(pixel);
    }
}
