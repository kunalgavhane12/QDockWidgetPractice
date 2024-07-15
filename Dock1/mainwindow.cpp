#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QLabel>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);

    QImage *image = new QImage(this->size() ,QImage::Format_RGB32);

    image->fill(Qt::green);

    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(QPixmap::fromImage(*image));

    QDockWidget *dock = new QDockWidget("", this);
    dock->setWidget(imageLabel);

    addDockWidget(Qt::RightDockWidgetArea, dock);

    setCentralWidget(dock);
}

MainWindow::~MainWindow()
{
    delete ui;
}

