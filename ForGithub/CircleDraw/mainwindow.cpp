#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createCircle(600,600);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow :: createCircle(int width,int height){
    circle= new Circle (this,width,height);
    circle->setGeometry(10,10,width,height);
    circle->show();
}
void MainWindow::on_pushButton_clicked()
{
    int valueOfLineEdit=ui->lineEdit->text().toInt();
    circle->drawCircleBresenham(circle->lastClickPoint,valueOfLineEdit);
    circle->lastClickPoints.clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    circle->drawPolygon();
}

void MainWindow::on_pushButton_3_clicked()
{
    circle->drawLineBresenham(circle->lastClickPoints.last(),circle->lastClickPoints[circle->lastClickPoints.length()-2]);
    circle->lastClickPoints.clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    circle->fillArea(circle->lastClickPoint.x()+1,circle->lastClickPoint.y(),qRgb(0,0,0),circle->color);
    circle->setPixmapPublic();
    circle->lastClickPoints.clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    bool res=circle->isPointInPolygon(circle->preLastClickPoints,circle->lastClickPoint);
    if(res){
        qInfo( "Is point in Polygon: YES");
    }
    else{
        qInfo( "Is point in Polygon: NO");
    }

}

void MainWindow::on_pushButton_6_clicked()
{
    circle->draw10Circles();
}

void MainWindow::on_pushButton_7_clicked()
{
    int valueOfLineEdit=ui->lineEdit->text().toInt();
    circle->drawFilledCircle(circle->lastClickPoint,valueOfLineEdit);
    circle->lastClickPoints.clear();
}
