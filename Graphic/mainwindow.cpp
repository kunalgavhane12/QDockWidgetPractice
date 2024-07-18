#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>
#include "customview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    view = new QGraphicsView(this);

    view = new CustomView(this);
    scene = new CustomScene(this);
    view->setScene(scene);
    setCentralWidget(view);

    createToolbar();

    zoomFactor = 1.5;

    setWindowTitle(tr("Test"));

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveAsFile);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);

    connect(ui->actionCut, &QAction::triggered, scene, &CustomScene::cut);
    connect(ui->actionCopy, &QAction::triggered, scene, &CustomScene::copy);
    connect(ui->actionPaste, &QAction::triggered, scene, &CustomScene::paste);
    connect(ui->actionUndo, &QAction::triggered, scene, &CustomScene::undo);
    connect(ui->actionRedo, &QAction::triggered, scene, &CustomScene::redo);

    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::zoomOut);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{

}

void MainWindow::saveFile()
{

}

void MainWindow::saveAsFile()
{

}

void MainWindow::zoomIn()
{
    zoomFactor *= 1.5;
    view->scale(1.5, 1.5);
}

void MainWindow::zoomOut()
{
    zoomFactor /= 1.5;
    view->scale(1.0 / 1.5, 1.0 / 1.5);
}

void MainWindow::createToolbar()
{
    QToolBar *toolBar = addToolBar(tr("Shapes"));

    rectButton = new ShapeButton(":/Icon/rect.png", ShapeButton::Rectangle, scene);
    ellipseButton = new ShapeButton(":/Icon/ellipse.png", ShapeButton::Ellipse, scene);
    lineButton = new ShapeButton(":/Icon/line.png", ShapeButton::Line, scene);
    roundedRectangle = new ShapeButton(":/Icon/roundrectangle.png", ShapeButton::RoundedRectangle, scene);
    squareDashed = new ShapeButton(":/Icon/square-dashed.svg", ShapeButton::SquareRectangle, scene);
    triangleButton = new ShapeButton(":/Icon/pyramid.svg", ShapeButton::TriangleRectangle, scene);
    polygonButton = new ShapeButton(":/Icon/polygon.png", ShapeButton::Polygon, scene);

    toolBar->addWidget(rectButton);
    toolBar->addWidget(ellipseButton);
    toolBar->addWidget(lineButton);
    toolBar->addWidget(roundedRectangle);
    toolBar->addWidget(squareDashed);
    toolBar->addWidget(triangleButton);
    toolBar->addWidget(polygonButton);

    addToolBar(toolBar);
}
