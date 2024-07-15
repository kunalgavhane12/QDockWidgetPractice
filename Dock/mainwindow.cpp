#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image = new QImage(this->size(), QImage::Format_RGB32);
    image->fill(Qt::white);

    setCentralWidget(centralWidget());

    connect(ui->actionRectangle, &QAction::triggered, this, &MainWindow::setshapeRectangle);
    connect(ui->actionLine, &QAction::triggered, this, &MainWindow::setshapeLine);
    connect(ui->actionOval, &QAction::triggered, this, &MainWindow::setshapeCircle);

    shape = None;
    selectedShape = None;
    resizing = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete image;
}

void MainWindow::setshapeRectangle()
{
    shape = Rectangle;
}

void MainWindow::setshapeLine()
{
    shape = Line;
}

void MainWindow::setshapeCircle()
{
    shape = Circle;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    drawShapes(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (shape == Rectangle)
        {
            currentRect.setTopLeft(event->pos());
            currentRect.setBottomRight(event->pos());
        }
        else if (shape == Line)
        {
            currentLine.setP1(event->pos());
            currentLine.setP2(event->pos());
        }
        else if (shape == Circle)
        {
            currentCircle.setTopLeft(event->pos());
            currentCircle.setBottomRight(event->pos());
        }
        update();
    }
    dragStartPosition = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (shape == Rectangle)
        {
            currentRect.setBottomRight(event->pos());
        }
        else if (shape == Line)
        {
            currentLine.setP2(event->pos());
        }
        else if (shape == Circle)
        {
            currentCircle.setBottomRight(event->pos());
        }
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (shape == Rectangle)
        {
            rectangles.append(currentRect.normalized());
        }
        else if (shape == Line)
        {
            lines.append(currentLine);
        }
        else if (shape == Circle)
        {
             circles.append(currentCircle);
        }

        currentRect = QRect();
        currentLine = QLineF();
        currentCircle = QRect();
        update();
    }
}

void MainWindow::drawShapes(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);

    foreach (const QRect &rect, rectangles)
    {
        painter.drawRect(rect);
    }

    foreach (const QLineF &line, lines)
    {
        painter.drawLine(line);
    }

    foreach (const QRect &rect, circles)
    {
        painter.drawEllipse(rect);
    }

    if (!currentRect.isNull() && shape == Rectangle)
    {
        painter.drawRect(currentRect);
    }

    if (!currentLine.isNull() && shape == Line)
    {
        painter.drawLine(currentLine);
    }

    if (!currentCircle.isNull() && shape == Circle)
    {
         painter.drawEllipse(currentCircle);
    }
}
