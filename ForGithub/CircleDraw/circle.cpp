#include "circle.h"
#include <qmath.h>

Circle::Circle(QWidget *parent,int width,int height) : QLabel(parent)
{
    background=QImage(width,height,QImage::Format_RGB32);
    color=qRgb(255,255,0);
    setPixmap(QPixmap ::fromImage(background));
}

void Circle::mousePressEvent(QMouseEvent *ev)
{
    lastClickPoint=ev->pos();
    lastClickPoints.append(lastClickPoint);
    background.setPixel(ev->pos().x(),ev->pos().y(),color);
    setPixmap(QPixmap::fromImage(background));
}

void Circle :: setPixmapPublic(){
    setPixmap(QPixmap::fromImage(background));
}

void Circle::drawCircle(QPoint centerPoint,int r)
{
    double x, y;
    double aci = 0.0;
    while (aci < 360) {
 //        QApplication::processEvents();
         x = centerPoint.x() + r * cos(qDegreesToRadians(aci));
         y = centerPoint.y() + r * sin(qDegreesToRadians(aci));
         aci += 1.0;
         background.setPixel(round(x), round(y), color);
         setPixmap(QPixmap::fromImage(background));
    }
}

void Circle::drawFilledCircle(QPoint centerPoint,float r)
{
    int x, y;
    for (x = -r; x <= r; ++x) {
        int YeniY = sqrt(r * r - x * x);
        for (y = -YeniY; y <= YeniY; ++y) {

            background.setPixel(centerPoint.x() + x, centerPoint.y() +y, color);
            setPixmap(QPixmap::fromImage(background));
        }
    }
}
void Circle:: drawCircleBresenham(QPoint centerPoint,float radius){
    int x=radius,y=0,error=0;
    int error1,error2;
    set8pixels(centerPoint,x,y);
    while(x>=y){
        error1=error+(2*y+1);
        error2=error+(2*y+1)+(-2*x+1);
        if(abs(error1) < abs(error2)){
            y++;
            error=error1;
        }else{
            x--;
            y++;
            error=error2;
        }
       set8pixels(centerPoint,x,y);
    }
    setPixmap(QPixmap::fromImage(background));
}
void Circle:: set8pixels(QPoint centerPoint,int x,int y){
    background.setPixel(centerPoint.x()+x,centerPoint.y()+y,color);
    background.setPixel(centerPoint.x()+x,centerPoint.y()-y,color);
    background.setPixel(centerPoint.x()+y,centerPoint.y()+x,color);
    background.setPixel(centerPoint.x()+y,centerPoint.y()-x,color);
    background.setPixel(centerPoint.x()-x,centerPoint.y()+y,color);
    background.setPixel(centerPoint.x()-x,centerPoint.y()-y,color);
    background.setPixel(centerPoint.x()-y,centerPoint.y()+x,color);
    background.setPixel(centerPoint.x()-y,centerPoint.y()-x,color);
}
void Circle:: drawPolygon(){
    int size=lastClickPoints.length();
    for (int i=0;i<=size;i++) {
        drawLineDDA(lastClickPoints[i%size],lastClickPoints[(i+1)%size]);
    }
    preLastClickPoints=lastClickPoints;
    lastClickPoints.clear();
}
bool Circle :: isPointInPolygon(QList<QPoint> PolygonPointList ,QPoint clickedPoint){
    QPoint maxPoint =getLastXPoint(PolygonPointList);
    QPoint tempLastPoint=QPoint (clickedPoint.x()+1,clickedPoint.y()) ;
    int counter=0;
    while(tempLastPoint.x() < maxPoint.x()+1){
        if(background.pixel(tempLastPoint.x(),tempLastPoint.y()) == color){
            counter++;
        }
        tempLastPoint.setX(tempLastPoint.x()+1);
    }
    if(counter % 2 == 0){
        return false;
    }else{
        return true;
    }
}
QPoint Circle :: getLastXPoint(QList<QPoint> PolygonPointList){
    int maxValue=PolygonPointList[0].x(),index=0;
    for (int i=1;i<PolygonPointList.length();i++) {
        if(PolygonPointList[i].x()>maxValue){
            maxValue=PolygonPointList[i].x();
            index=i;
        }
    }
    return preLastClickPoints[index];
}
void Circle::drawLineDDA(QPoint firstPoint,QPoint secondPoint)
{
    double dx = secondPoint.x() - firstPoint.x();
    double dy = secondPoint.y() - firstPoint.y();
    double Xdiff;
    double Ydiff;
    double x;
    double y;
    double pixelCount;
    if (fabs(dx) > fabs(dy)) {
        pixelCount = fabs(dx);
    } else {
        pixelCount = fabs(dy);
    }
    Xdiff = dx / pixelCount;
    Ydiff = dy / pixelCount;
    x = firstPoint.x();
    y = firstPoint.y();
    for (int i = 0; i < pixelCount ;++i ) {
        x += Xdiff;
        y += Ydiff;
        background.setPixel(round(x), round(y), color);
    }
    setPixmap(QPixmap::fromImage(background));
}
void Circle::drawLineBresenham(QPoint firstPoint,QPoint secondPoint)
{
    int dx = secondPoint.x() - firstPoint.x();
    int dy = secondPoint.y() - firstPoint.y();
    if (abs(dx) - abs(dy) > 0) {
        if (dx > 0) {
            if (dy > 0) {
                xZone(firstPoint,firstPoint.x() - secondPoint.x(), 1, 1, abs(dx), 2 * abs(dx), 2 * abs(dy));
            } else {
                xZone(firstPoint,firstPoint.x() - secondPoint.x(), 1, -1, abs(dx), 2 * abs(dx), 2 * abs(dy));
            }
        } else {
            if (dy > 0) {
                xZone(firstPoint,secondPoint.x() - firstPoint.x(), -1, 1, abs(dx), 2 * abs(dx), 2 * abs(dy));
            } else {
                xZone(firstPoint,secondPoint.x() - firstPoint.x(), -1, -1, abs(dx), 2 * abs(dx), 2 * abs(dy));
            }
        }
    } else {
        if (dy > 0) {
            if (dx > 0) {
                yZone(firstPoint,firstPoint.y() - secondPoint.y(), 1, 1, abs(dy), 2 * abs(dx), 2 * abs(dy));
            } else {
                yZone(firstPoint,firstPoint.y() - secondPoint.y(), -1, 1, abs(dy), 2 * abs(dx), 2 * abs(dy));
            }
        } else {
            if (dx > 0) {
                yZone(firstPoint,secondPoint.y() - firstPoint.y(), 1, -1, abs(dy), 2 * abs(dx), 2 * abs(dy));
            } else {
                yZone(firstPoint,secondPoint.y() - firstPoint.y(), -1, -1, abs(dy), 2 * abs(dx), 2 * abs(dy));
            }
        }
    }
    setPixmap(QPixmap::fromImage(background));
}

void Circle::fillArea(int x, int y, QRgb floorColor, QRgb newColor)
{
    if(background.pixel(x,y) == floorColor){
        background.setPixel(x,y,newColor);
        fillArea(x+1,y,floorColor,newColor);
        fillArea(x-1,y,floorColor,newColor);
        fillArea(x,y+1,floorColor,newColor);
        fillArea(x,y-1,floorColor,newColor);
    }
}


void Circle::yZone(QPoint firstPoint,int error, int Xrise, int Yrise, int pixelCount, int dx2, int dy2)
{
    int x1 = firstPoint.x();
    int y1 = firstPoint.y();
    int x = x1;
    for (int i = 0; i < pixelCount; ++i) {
        background.setPixel(x, y1, color);
        error += dx2;
        if (error > 0) {
            x += Xrise;
            error -= dy2;
        }
        y1 += Yrise;
    }
}

void Circle::xZone(QPoint firstPoint,int error, int Xrise, int Yrise, int pixelCount, int dx2, int dy2)
{
    int x1 = firstPoint.x();
    int y1 = firstPoint.y();
    int y = y1;
    for (int i = 0; i < pixelCount; ++i) {
        background.setPixel(x1, y, color);
        error += dy2;
        if (error > 0) {
            y += Yrise;
            error -= dx2;
        }
        x1 += Xrise;
    }
}
void Circle :: draw10Circles(){
    int x=100,y=100;
    while(y < 600){
        if(x>500){
            x=100;
            y+=200;
        }
        drawCircleBresenham(QPoint(x,y),100);
        x+=200;
    }
    drawCircleBresenham(QPoint(300,300),300);
}
