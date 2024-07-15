#include "canvaswidget.h"
#include <QMouseEvent>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent), drawMode(None)
{
    setMouseTracking(true);
}

void CanvasWidget::setDrawModeRectangle()
{
    drawMode = Rectangle;
}

void CanvasWidget::setDrawModeLine()
{
    drawMode = Line;
}
void CanvasWidget::setDrawModeCircle()
{
    drawMode = Circle;
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    drawShapes(painter);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (drawMode == Rectangle)
        {
            currentRect.setTopLeft(event->pos());
            currentRect.setBottomRight(event->pos());
        }
        else if (drawMode == Line)
        {
            currentLine.setP1(event->pos());
            currentLine.setP2(event->pos());
        }
        else if (drawMode == Circle)
        {
            currentCircle.setTopLeft(event->pos());
            currentCircle.setBottomRight(event->pos());
        }
        update();
    }
    dragStartPosition = event->pos();
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (drawMode == Rectangle)
        {
            currentRect.setBottomRight(event->pos());
        }
        else if (drawMode == Line)
        {
            currentLine.setP2(event->pos());
        }
        else if (drawMode == Circle)
        {
            currentCircle.setBottomRight(event->pos());
        }
        update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (drawMode == Rectangle)
        {
            rectangles.append(currentRect.normalized());
        }
        else if (drawMode == Line)
        {
            lines.append(currentLine);
        }
        else if (drawMode == Circle)
        {
             circles.append(currentCircle);
        }

        currentRect = QRect();
        currentLine = QLineF();
        currentCircle = QRect();
        update();
    }
}

void CanvasWidget::drawShapes(QPainter &painter)
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

    if (!currentRect.isNull() && drawMode == Rectangle)
    {
        painter.drawRect(currentRect);
    }

    if (!currentLine.isNull() && drawMode == Line)
    {
        painter.drawLine(currentLine);
    }

    if (!currentCircle.isNull() && drawMode == Circle)
    {
         painter.drawEllipse(currentCircle);
    }
}
