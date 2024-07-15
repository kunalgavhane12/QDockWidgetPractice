#include "mainwindow.h"
#include "linewidget.h"
#include "rectanglewidget.h"
#include "circlewidget.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setAcceptDrops(true);

    dockLineWidget = new QDockWidget(tr("Line"), this);
    LineWidget *lineWidget = new LineWidget(dockLineWidget);
    dockLineWidget->setWidget(lineWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockLineWidget);

    dockRectWidget = new QDockWidget(tr("Rectangle"), this);
    RectangleWidget *rectWidget = new RectangleWidget(dockRectWidget);
    dockRectWidget->setWidget(rectWidget);
    addDockWidget(Qt::RightDockWidgetArea, dockRectWidget);

    dockCircleWidget = new QDockWidget(tr("Circle"), this);
    CircleWidget *circleWidget = new CircleWidget(dockCircleWidget);
    dockCircleWidget->setWidget(circleWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockCircleWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    if (event->mimeData()->text() == "LineWidget")
    {
        LineWidget *lineWidget = new LineWidget(this);
        lineWidget->move(event->pos());
        lineWidget->show();
    }
    else if (event->mimeData()->text() == "RectangleWidget")
    {
        RectangleWidget *rectWidget = new RectangleWidget(this);
        rectWidget->move(event->pos());
        rectWidget->show();
    }
    else if (event->mimeData()->text() == "CircleWidget")
    {
        CircleWidget *circleWidget = new CircleWidget(this);
        circleWidget->move(event->pos());
        circleWidget->show();
    }
}
