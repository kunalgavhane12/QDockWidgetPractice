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
    if (event->mimeData()->hasText() && (event->mimeData()->text() == QString::number(ShapeButton::Rectangle) || event->mimeData()->text() == QString::number(ShapeButton::Ellipse))) {
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
}

void CustomScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
}

void CustomScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        ShapeButton::ShapeType shapeType = static_cast<ShapeButton::ShapeType>(event->mimeData()->text().toInt());
        switch (shapeType) {
        case ShapeButton::Rectangle:
            draggedItem = addRect(event->scenePos().x(), event->scenePos().y(), 100, 50, QPen(Qt::black), QBrush(Qt::blue));
            break;
        case ShapeButton::Ellipse:
            draggedItem = addEllipse(event->scenePos().x(), event->scenePos().y(), 50, 50, QPen(Qt::black), QBrush(Qt::green));
            break;
        default:
            break;
        }

        draggedItem->setFlag(QGraphicsItem::ItemIsMovable);
        draggedItem->setFlag(QGraphicsItem::ItemIsSelectable);
        draggedItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

        isDragging = true;
        dragStartPosition = event->scenePos();
        lastMousePos = event->scenePos();
    }
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        if (QGraphicsItem *item = itemAt(event->scenePos(), QTransform())) {
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

    if (isDragging && draggedItem) {
        QPointF newPos = event->scenePos();
        QPointF delta = newPos - lastMousePos;

        if (event->modifiers() & Qt::ShiftModifier) {
            qreal scaleFactor = 1.1;
            if (delta.x() > 0)
                draggedItem->setScale(draggedItem->scale() * scaleFactor);
            else
                draggedItem->setScale(draggedItem->scale() / scaleFactor);
        } else {
            draggedItem->setPos(draggedItem->pos() + delta);
        }

        lastMousePos = newPos;
    }
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if (isDragging && event->button() == Qt::LeftButton) {
        isDragging = false;
        draggedItem = nullptr;
    }
}
