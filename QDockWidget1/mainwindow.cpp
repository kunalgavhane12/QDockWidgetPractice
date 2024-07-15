#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PaintArea.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QDockWidget *dock = new QDockWidget(tr("Line"), this);
    PaintArea *paintArea = new PaintArea(dock);
    dock->setWidget(paintArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    setCentralWidget(dock);
}

MainWindow::~MainWindow() {
    delete ui;
}
