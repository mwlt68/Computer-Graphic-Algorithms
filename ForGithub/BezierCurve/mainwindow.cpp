#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int width=500,height=500;
    myLabel = new MyLabel(this,width,height);
    myLabel->setGeometry(10,10,width,height);
    myLabel->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

