#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->dockWidget);
    QImage *image = new QImage(ui->label->size(),QImage::Format_RGB32);
    image->fill(Qt::green);
    ui->label->setPixmap(QPixmap::fromImage(*image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

