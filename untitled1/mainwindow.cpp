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

    setCentralWidget(dock);

    connect(ui->actionRectangle, &QAction::triggered, obj, &CanvasWidget::setDrawModeRectangle);
    connect(ui->actionLine, &QAction::triggered, obj, &CanvasWidget::setDrawModeLine);
    connect(ui->actionCircle, &QAction::triggered, obj, &CanvasWidget::setDrawModeCircle);
}

MainWindow::~MainWindow()
{
    delete ui;
}
