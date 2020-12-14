#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr,int width=100,int height=100);
    QPoint size;
    QPoint rectSize;
    QRgb color;
    bool isMovable=false;
    int indexForMove;
    QPoint previousPoint;
    QList<QPoint> selectedPoints;

signals:

public slots:
    QList<QRect> getRects();
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;
    void drawRectangles();
    void drawFrameRectangles();
    int getPointInRectangles(QPoint point);
    QList<QPoint> getBezierCurvePoints();
    void drawBezierPoints();
    void drawPointLines();
};

#endif // MYLABEL_H
