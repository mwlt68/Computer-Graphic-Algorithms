#ifndef CIRCLE_H
#define CIRCLE_H

#include <QLabel>
#include <QMouseEvent>
#include <math.h>

class Circle : public QLabel
{
    Q_OBJECT
public:
    explicit Circle(QWidget *parent = nullptr,int width=100,int height=100);
    QRgb color;
    QList<QPoint> lastClickPoints;
    QList<QPoint> preLastClickPoints;
    QPoint lastClickPoint;
private:
    void mousePressEvent(QMouseEvent *ev) override;
    QImage background;

signals:

public slots:
    void setPixmapPublic();
    void drawCircle(QPoint centerPoint,int r);
    void drawFilledCircle(QPoint centerPoint,float r);
    void drawCircleBresenham(QPoint centerPoint,float radius);
    void drawPolygon();
    void drawLineDDA(QPoint firstPoint,QPoint secondPoint);
    void drawLineBresenham(QPoint firstPoint,QPoint secondPoint);
    void fillArea(int x,int y,QRgb floorColor,QRgb newColor);
    bool isPointInPolygon(QList<QPoint> PolygonPointList ,QPoint clickedPoint);
    void draw10Circles();
private slots:
    void yZone(QPoint firstPoint,int error, int Xrise, int Yrise, int pixelCount, int dx2, int dy2);
    void xZone(QPoint firstPoint,int error, int Xrise, int Yrise, int pixelCount, int dx2, int dy2);
    void set8pixels(QPoint centerPoint,int x,int y);
    QPoint getLastXPoint(QList<QPoint> PolygonPointList);
};

#endif // CIRCLE_H
