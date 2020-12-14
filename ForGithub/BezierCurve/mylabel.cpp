#include "mylabel.h"
#include "qmath.h"
MyLabel::MyLabel(QWidget *parent,int width,int height) : QLabel(parent)
{
    size=QPoint(width,height);
    color=qRgb(255,255,0);
    rectSize=QPoint(10,10);
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton){
        int index= getPointInRectangles(ev->pos());
        if(index>=0 && index < selectedPoints.length()){
            isMovable=true;
            indexForMove=index;
            previousPoint=ev->pos();
        }
        else{
            isMovable=false;
            selectedPoints.append(ev->pos());
            update();
        }
    }
    else if(ev->button() == Qt::RightButton){
        int index= getPointInRectangles(ev->pos());
        if(index>=0 && index < selectedPoints.length()){
            isMovable=false;
           selectedPoints.removeAt(index);
            update();
        }
    }
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(isMovable){
        QPoint diff=ev->pos()-previousPoint;
        previousPoint=ev->pos();
        QPoint newPoint(selectedPoints[indexForMove].x()+diff.x(),selectedPoints[indexForMove].y()+diff.y());
        selectedPoints[indexForMove]=newPoint;
        update();
    }
}
void MyLabel::paintEvent(QPaintEvent *)
{
    drawFrameRectangles();
    drawPointLines();
    drawBezierPoints();
    drawRectangles();
}
void MyLabel:: drawBezierPoints(){
    if(selectedPoints.length()<2){
        return;
    }
    QList<QPoint> points = getBezierCurvePoints();
    QPainter painter(this);
    QPen pen(Qt::red,2);
    painter.setPen(pen);
    foreach (QPoint point, points) {
        painter.drawPoint(point);
    }
}

void MyLabel:: drawPointLines(){
    QPen pen(Qt::blue,1);
    QPainter painter(this);
    painter.setPen(pen);
    for (int i=0;i<selectedPoints.length()-1;i++) {
        painter.drawLine(selectedPoints[i],selectedPoints[i+1]);
    }
}
void MyLabel:: drawFrameRectangles(){
     QPainter painter(this);
     QPen pen(Qt::green,5);
     painter.setPen(pen);
     painter.drawRect(QRect(0,0,size.x(),size.y()));
}
void MyLabel::drawRectangles(){
    QPainter painter(this);
    QBrush brush(color,Qt::SolidPattern);
    painter.setBrush(brush);
    QList<QRect> rects= getRects();
    foreach (QRect rect, rects) {
        painter.drawRect(rect);
    }
}
QList<QRect> MyLabel:: getRects(){
    QList<QRect> rects;
    foreach (QPoint point, selectedPoints) {
        int rectX=point.x()-(rectSize.x()/2);
        int rectY=point.y()-(rectSize.y()/2);
        QRect rect(rectX,rectY,rectSize.x(),rectSize.y());
        rects.append(rect);
    }
    return rects;
}
int MyLabel:: getPointInRectangles(QPoint point){
    QList<QRect> rects=getRects();
    for (int i =0;i<selectedPoints.length();i++) {
            if(rects[i].contains(point)){
                return i;
            }
    }
    return -1;
}
int Combination(int size,int i){
    int result = 1;
    for(int j=(i+1) ; j<=size ; j++){

        result*=j;
    }
    for(int j=1 ; j <= (size-i) ; j++){

        result/=j;
    }
    return result;
}
float basisFunction(int i , int size, float u){
    float combination = Combination(size,i);
    for(int j=1 ; j<=i ; j++){

        combination*=u;
    }
    for(int j=1 ; j <= (size-i) ; j++){

        combination*=(1-u);
    }
    return combination;
}
QPoint getBezierPoint(float u,QList<QPoint> selectedPoints){
    float x=0,y=0;
    int size=selectedPoints.length()-1;
    for (int i =0;i<=size ;i++) {
       float  basis=basisFunction(i,size,u);
       x+=selectedPoints[i].x()*basis;
       y+=selectedPoints[i].y()*basis;
    }
    QPoint point((int)(x+0.5),(int)(y+0.5));
    return point;
}
QList<QPoint> MyLabel:: getBezierCurvePoints(){
    QList<QPoint> points;
    double x;
    double y;
    for(float u=0.0005;u<=1;u+=0.0005)
      {
       QPoint point= getBezierPoint( u,selectedPoints);
       points.append(point);
   }
    return points;
}
