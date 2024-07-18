#include "customscene.h"
#include "shapebutton.h"

#include <QMimeData>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QDebug>

CustomScene::CustomScene(QObject *parent)
    : QGraphicsScene(parent), isDragging(false), draggedItem(nullptr)
{
    setSceneRect(0, 0, 800, 600);
}


void CustomScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText() && (event->mimeData()->text() == QString::number(ShapeButton::Rectangle)
                                         || event->mimeData()->text() == QString::number(ShapeButton::Ellipse)))
    {
        qDebug() << event->mimeData()->hasText();
        qDebug() << event->mimeData()->text();
        qDebug() << QString::number(ShapeButton::Rectangle);
        event->setAccepted(true);
    }
    else
    {
        event->setAccepted(false);
    }
}

void CustomScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
}

void CustomScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        ShapeButton::ShapeType shapeType = static_cast<ShapeButton::ShapeType>(event->mimeData()->text().toInt());
        switch (shapeType)
        {
        case ShapeButton::Rectangle:
            draggedItem = addRect(event->scenePos().x(), event->scenePos().y(), 100, 50, QPen(Qt::black), QBrush(Qt::blue));
            break;
        case ShapeButton::Ellipse:
            draggedItem = addEllipse(event->scenePos().x(), event->scenePos().y(), 50, 50, QPen(Qt::black), QBrush(Qt::green));
            break;
        case ShapeButton::Line:
            break;
        case ShapeButton::TriangleRectangle:
            break;
        case ShapeButton::RoundedRectangle:
            break;
        case ShapeButton::SquareRectangle:
            break;
        case ShapeButton::Polygon:
            break;
        default:
            break;
        }

        draggedItem->setFlag(QGraphicsItem::ItemIsMovable);
        draggedItem->setFlag(QGraphicsItem::ItemIsSelectable);
        draggedItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

        undoStack.push_back(draggedItem);
        isDragging = true;
        dragStartPosition = event->scenePos();
        lastMousePos = event->scenePos();
    }
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
    {
        if (QGraphicsItem *item = itemAt(event->scenePos(), QTransform()))
        {
            draggedItem = item;
            isDragging = true;
            dragStartPosition = event->scenePos();
            lastMousePos = event->scenePos();
        }
    }
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if (isDragging && draggedItem)
    {
        QPointF newPos = event->scenePos();
        QPointF delta = newPos - lastMousePos;

        if (event->modifiers() & Qt::ShiftModifier)
        {
            qreal scaleFactor = 1.1;
            if (delta.x() > 0)
                draggedItem->setScale(draggedItem->scale() * scaleFactor);
            else
                draggedItem->setScale(draggedItem->scale() / scaleFactor);
        }
        else
        {
            draggedItem->setPos(draggedItem->pos() + delta);
        }

        lastMousePos = newPos;
    }
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if (isDragging && event->button() == Qt::LeftButton)
    {
        isDragging = false;
        draggedItem = nullptr;
    }
}

void CustomScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter;
    //    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    //    painter.drawLine(0, 0, 200, 200);

    QPen pen(Qt::black);
    pen.setWidth(6);
    QPen linePen(Qt::red);
    linePen.setWidth(2);

    QPoint p1;
    p1.setX(10);
    p1.setY(30);

    QPoint p2;
    p2.setX(100);
    p2.setY(30);


    //    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(linePen);
    painter.drawLine(p1, p2);

    painter.setPen(pen);
    painter.drawPoint(p1);
    painter.drawPoint(p2);

}

void CustomScene::cut()
{

}
void CustomScene::copy()
{

}
void CustomScene::paste()
{

}

void CustomScene::undo()
{
    if (!undoStack.isEmpty()) {
        QGraphicsItem *item = undoStack.pop();
        redoStack.push(item);
        removeItem(item);
    }
}

void CustomScene::redo()
{
    if (!redoStack.isEmpty()) {
        QGraphicsItem *item = redoStack.pop();
        undoStack.push(item);
        addItem(item);
    }
}

