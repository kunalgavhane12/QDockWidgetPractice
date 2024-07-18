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

    undoStack = new QUndoStack(this);

    setWindowTitle(tr("Draggable Shapes"));

    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::zoomOut);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redo);

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::undo()
{
    undoStack->undo();
}

void MainWindow::redo()
{
    undoStack->redo();
}

void MainWindow::createToolbar()
{
    QToolBar *toolBar = addToolBar(tr("Shapes"));

    rectButton = new ShapeButton(":/Icon/rect.png", ShapeButton::Rectangle, scene);
    ellipseButton = new ShapeButton(":/Icon/ellipse.png", ShapeButton::Ellipse, scene);
    lineButton = new ShapeButton(":/Icon/line.png", ShapeButton::Rectangle, scene);
    roundedRectangle = new ShapeButton(":/Icon/roundrectangle.png", ShapeButton::Rectangle, scene);
    squareDashed = new ShapeButton(":/Icon/square-dashed.svg", ShapeButton::Rectangle, scene);
    undoButton = new ShapeButton(":/Icon/Undo.png", ShapeButton::Rectangle, scene);
    redoButton = new ShapeButton(":/Icon/Redo.png", ShapeButton::Rectangle, scene);

    toolBar->addWidget(rectButton);
    toolBar->addWidget(ellipseButton);
    toolBar->addWidget(lineButton);
    toolBar->addWidget(roundedRectangle);
    toolBar->addWidget(squareDashed);
    toolBar->addWidget(undoButton);
    toolBar->addWidget(redoButton);

    addToolBar(toolBar);
}
