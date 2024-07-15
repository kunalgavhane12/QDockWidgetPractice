#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include "canvaswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDockWidget *dock = new QDockWidget(tr("Drawing"), this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    obj = new CanvasWidget(this);
    dock->setWidget(obj);

    connect(ui->pushButton, &QPushButton::clicked, obj, &CanvasWidget::setDrawModeRectangle);
    connect(ui->pushButton_2, &QPushButton::clicked, obj, &CanvasWidget::setDrawModeLine);
    connect(ui->pushButton_3, &QPushButton::clicked, obj, &CanvasWidget::setDrawModeCircle);
}

MainWindow::~MainWindow()
{
    delete ui;
}
