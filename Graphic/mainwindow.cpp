#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QTextStream>
#include <QWheelEvent>
#include <QColorDialog>
#include <QInputDialog>
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

    connect(ui->actionUndo, &QAction::triggered, scene, &CustomScene::undo);
    connect(ui->actionRedo, &QAction::triggered, scene, &CustomScene::redo);

    connect(ui->actionPen_Color, &QAction::triggered, this, &MainWindow::penColor);
    connect(ui->actionPen_Size, &QAction::triggered, this, &MainWindow::penWidth);
//    connect(ui->actionEdit, &QAction::triggered, scene, &CustomScene::drawShapes);

    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::zoomOut);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::penColor()
{
//    QColor newColor = QColorDialog::getColor(scene->penColor());
//    if(newColor.isValid())
//    {
//        scene->setPenColor(newColor);
//    }

}

void MainWindow::penWidth()
{
//    bool ok;
//    int newWidth = QInputDialog::getInt(this, "View", "Select pen width : ",
//                                        scene->penWidth(),1,50,1,&ok);

//    if(ok)
//    {
//        scene->setPenWidth(newWidth);
//    }
}

void MainWindow::newFile()
{
    scene->clear();
    setCurrentFile(QString());
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JSON Files (*.json);;XML Files (*.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Open File"), tr("Cannot open file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }

    if (fileName.endsWith(".json"))
    {
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        scene->loadFromJson(doc.object());
    }
    else if (fileName.endsWith(".xml"))
    {
        QDomDocument doc;
        if (!doc.setContent(&file))
        {
            QMessageBox::warning(this, tr("Open File"), tr("Cannot parse file %1:\n%2.").arg(fileName).arg(file.errorString()));
            return;
        }
        QDomElement root = doc.documentElement();
        scene->loadFromXml(root);
    }

    setCurrentFile(fileName);
}

void MainWindow::saveFile()
{
    if (currentFile.isEmpty())
    {
        saveAsFile();
    }
    else
    {
        QFile file(currentFile);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(this, tr("Save File"), tr("Cannot save file %1:\n%2.").arg(currentFile).arg(file.errorString()));
            return;
        }

        if (currentFile.endsWith(".json"))
        {
            QJsonObject sceneObject;
            scene->saveToJson(sceneObject);
            QJsonDocument doc(sceneObject);
            file.write(doc.toJson());
        }
        else if (currentFile.endsWith(".xml"))
        {
            QDomDocument doc;
            QDomElement root = doc.createElement("scene");
            doc.appendChild(root);
            scene->saveToXml(doc, root);
            QTextStream stream(&file);
            stream << doc.toString();
        }

        setCurrentFile(currentFile);
    }
}

void MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("JSON Files (*.json);;XML Files (*.xml)"));
    if (fileName.isEmpty())
        return;

    setCurrentFile(fileName);
    saveFile();
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
    rectButton = new ShapeButton(":/Icon/rect.png", ShapeButton::Rectangle, scene);
    ellipseButton = new ShapeButton(":/Icon/ellipse.png", ShapeButton::Ellipse, scene);
    lineButton = new ShapeButton(":/Icon/line.png", ShapeButton::Line, scene);
    roundedRectangle = new ShapeButton(":/Icon/roundrectangle.png", ShapeButton::RoundedRectangle, scene);
    triangleButton = new ShapeButton(":/Icon/pyramid.svg", ShapeButton::TriangleRectangle, scene);
    polygonButton = new ShapeButton(":/Icon/polygon.png", ShapeButton::Polygon, scene);

    ui->toolBar_2->addWidget(rectButton);
    ui->toolBar_2->addWidget(ellipseButton);
    ui->toolBar_2->addWidget(lineButton);
    ui->toolBar_2->addWidget(roundedRectangle);
    ui->toolBar_2->addWidget(triangleButton);
    ui->toolBar_2->addWidget(polygonButton);

}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    setWindowModified(false);
    setWindowFilePath(currentFile.isEmpty() ? tr("untitled.json") : currentFile);
}
