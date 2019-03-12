#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QRgb>

#define WIDTH 100
#define SIZE 100*100*4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    uchar* data=new uchar[SIZE];

    for(int x=0; x<WIDTH; x++){
        for(int y=0; y<WIDTH; y++){
            data[y*WIDTH*4+3*x]=0;
            data[y*WIDTH*4+3*x+1]=255;
            data[y*WIDTH*4+3*x+2]=0;
            data[y*WIDTH*4+4*x+3]=255;
        }
    }

    QImage im(WIDTH,WIDTH,QImage::Format_RGB888);

    QRgb value;
    for(int x=0; x<WIDTH; x++){
        for(int y=0; y<WIDTH; y++){
            value=qRgb(0, 0, 255);
            im.setPixel(x,y,value);
        }
    }

    qDebug() << "bytes per line" << im.bytesPerLine();

    scene=new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(im));
    scene->setSceneRect(im.rect());

    ui->mainImage->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Drawing an image using a QLabel seems like a bit of a kludge to me. With newer versions of Qt you can use a QGraphicsView widget. In Qt Creator, drag a Graphics View widget onto your UI and name it something (it is named mainImage in the code below). In mainwindow.h, add something like the following as private variables to your MainWindow class:

//QGraphicsScene *scene;
//QPixmap image;
//Then just edit mainwindow.cpp and make the constructor something like this:

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent), ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);

//    image.load("myimage.png");
//    scene = new QGraphicsScene(this);
//    scene->addPixmap(image);
//    scene->setSceneRect(image.rect());

//    ui->mainImage->setScene(scene);
//}
