#include "customscene.h"
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDomDocument>
#include <QDomElement>

CustomScene::CustomScene(QObject *parent)
    : QGraphicsScene(parent),
      defaultRectItem(nullptr),
      defaultEllipseItem(nullptr),
      defaultLineItem(nullptr),
      defaultTriangleItem(nullptr),
      defaultRoundedRectItem(nullptr),
      defaultSquareRectItem(nullptr),
      defaultPolygonItem(nullptr),
      draggedItem(nullptr),
      isDragging(false)
{
    setSceneRect(0, 0, 800, 600);
    initializeDefaultShapes();
}

void CustomScene::initializeDefaultShapes()
{
    defaultRectItem = new QGraphicsRectItem(0, 0, 100, 50);
    defaultEllipseItem = new QGraphicsEllipseItem(0, 0, 50, 50);
    defaultLineItem = new QGraphicsLineItem(10, 100, 100, 100);

    QPolygonF triangle;
//    triangle << QPointF(0, 0) << QPointF(50, 0) << QPointF(25, 50);
//    triangle << QPointF(0, 0) << QPointF(100, 0) << QPointF(50, 100);
    triangle << QPointF(0, 0) << QPointF(0, 100) << QPointF(100, 50);
    defaultTriangleItem = new QGraphicsPolygonItem(triangle);

    defaultRoundedRectItem = new QGraphicsRectItem(0, 0, 100, 50);
    defaultSquareRectItem = new QGraphicsRectItem(0, 0, 50, 50);

    QPolygonF polygon;
    polygon << QPointF(0, 0) << QPointF(50, 0) << QPointF(50, 50) << QPointF(0, 50);
    defaultPolygonItem = new QGraphicsPolygonItem(polygon);

    // Set default styles
    defaultRectItem->setPen(QPen(Qt::black));
    defaultRectItem->setBrush(QBrush(Qt::blue));
    defaultEllipseItem->setPen(QPen(Qt::black));
    defaultEllipseItem->setBrush(QBrush(Qt::green));
    defaultLineItem->setPen(QPen(Qt::black));
    defaultTriangleItem->setPen(QPen(Qt::black));
    defaultTriangleItem->setBrush(QBrush(Qt::yellow));
    defaultRoundedRectItem->setPen(QPen(Qt::black));
    defaultRoundedRectItem->setBrush(QBrush(Qt::cyan));
    defaultSquareRectItem->setPen(QPen(Qt::black));
    defaultSquareRectItem->setBrush(QBrush(Qt::magenta));
    defaultPolygonItem->setPen(QPen(Qt::black));
    defaultPolygonItem->setBrush(QBrush(Qt::red));
}

void CustomScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true);
    }
    else  if (event->mimeData()->hasImage())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->setAccepted(false);
    }
}

void CustomScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
    if (event->mimeData()->hasImage())
    {
           event->acceptProposedAction();
     }
}

void CustomScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        ShapeButton::ShapeType shapeType = static_cast<ShapeButton::ShapeType>(event->mimeData()->text().toInt());
        switch (shapeType)
        {
        case ShapeButton::Rectangle:
            draggedItem = new QGraphicsRectItem(defaultRectItem->rect());
            break;
        case ShapeButton::Ellipse:
            draggedItem = new QGraphicsEllipseItem(defaultEllipseItem->rect());
            break;
        case ShapeButton::Line:
            draggedItem = new QGraphicsLineItem(defaultLineItem->line());
            break;
        case ShapeButton::TriangleRectangle:
            draggedItem = new QGraphicsPolygonItem(defaultTriangleItem->polygon());
            break;
        case ShapeButton::RoundedRectangle:
            draggedItem = new QGraphicsRectItem(defaultRoundedRectItem->rect());
            break;
        case ShapeButton::Polygon:
            draggedItem = new QGraphicsPolygonItem(defaultPolygonItem->polygon());
            break;
        default:
            return;
        }

        if (draggedItem)
        {
            if (auto rectItem = dynamic_cast<QGraphicsRectItem*>(draggedItem))
            {
                rectItem->setPen(defaultRectItem->pen());
                rectItem->setBrush(defaultRectItem->brush());
            }
            else if (auto ellipseItem = dynamic_cast<QGraphicsEllipseItem*>(draggedItem))
            {
                ellipseItem->setPen(defaultEllipseItem->pen());
                ellipseItem->setBrush(defaultEllipseItem->brush());
            }
            else if (auto lineItem = dynamic_cast<QGraphicsLineItem*>(draggedItem))
            {
                lineItem->setPen(defaultLineItem->pen());
            }
            else if (auto polygonItem = dynamic_cast<QGraphicsPolygonItem*>(draggedItem))
            {
                polygonItem->setPen(defaultPolygonItem->pen());
                polygonItem->setBrush(defaultPolygonItem->brush());
            }

            draggedItem->setFlag(QGraphicsItem::ItemIsMovable);
            draggedItem->setFlag(QGraphicsItem::ItemIsSelectable);
            draggedItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
            draggedItem->setPos(event->scenePos());

            addItem(draggedItem);

            undoStack.push_back(draggedItem);
            isDragging = true;
            dragStartPosition = event->scenePos();
            lastMousePos = event->scenePos();
        }
    }
    else if (event->mimeData()->hasImage())
    {

        if (draggedPixmapItem)
        {
            removeItem(draggedPixmapItem);
            delete draggedPixmapItem;
        }

        QPointF position = event->scenePos();
        QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());

        draggedPixmapItem = addPixmap(QPixmap::fromImage(image));
        draggedPixmapItem->setPos(position);
        draggedPixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        draggedPixmapItem->setFlag(QGraphicsItem::ItemIsSelectable);
        draggedPixmapItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        draggedPixmapItem->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
//        draggedPixmapItem->setFlag(QGraphicsItem::ItemSendsTransformChanges);
        draggedPixmapItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        draggedPixmapItem->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
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
    QPen pen(Qt::black);
    pen.setWidth(6);
    QPen linePen(Qt::red);
    linePen.setWidth(2);

    QPoint p1(10, 30);
    QPoint p2(100, 60);
    painter.setPen(pen);
    painter.drawLine(p1, p2);

    painter.setPen(linePen);
    painter.drawLine(10, 30, 100, 60);

    painter.setPen(Qt::blue);
    painter.drawEllipse(QRect(20, 40, 60, 30));

    painter.setPen(Qt::green);
    painter.drawRect(QRect(50, 70, 80, 40));
}


void CustomScene::undo()
{
    if (!undoStack.isEmpty())
    {
        QGraphicsItem *item = undoStack.takeLast();
        redoStack.push_back(item);
        removeItem(item);
    }
}

void CustomScene::redo()
{
    if (!redoStack.isEmpty())
    {
        QGraphicsItem *item = redoStack.takeLast();
        undoStack.push_back(item);
        addItem(item);
    }
}

void CustomScene::saveToJson(QJsonObject &json)
{
    QJsonArray itemsArray;
    for (QGraphicsItem *item : items())
    {
        QJsonObject itemObject;
        itemObject["type"] = QString::number(item->type());
        itemObject["x"] = item->x();
        itemObject["y"] = item->y();
        itemObject["width"] = item->boundingRect().width();
        itemObject["height"] = item->boundingRect().height();
        itemsArray.append(itemObject);
    }
    json["items"] = itemsArray;
}

void CustomScene::loadFromJson(const QJsonObject &json)
{
    QJsonArray itemsArray = json["items"].toArray();
    for (const QJsonValue &value : qAsConst(itemsArray))
    {
        QJsonObject itemObject = value.toObject();
        int type = itemObject["type"].toInt();
        qreal x = itemObject["x"].toDouble();
        qreal y = itemObject["y"].toDouble();
        qreal width = itemObject["width"].toDouble();
        qreal height = itemObject["height"].toDouble();

        QGraphicsItem *item = nullptr;
        switch (type)
        {
        case QGraphicsRectItem::Type:
            item = new QGraphicsRectItem(x, y, width, height);
            break;
        case QGraphicsEllipseItem::Type:
            item = new QGraphicsEllipseItem(x, y, width, height);
            break;
        case QGraphicsLineItem::Type:
            item = new QGraphicsLineItem(x, y, width, height);
            break;
        case QGraphicsPolygonItem::Type:
            QPolygonF polygon;
             item = new QGraphicsPolygonItem(polygon);
            break;
        }

        if (item)
        {
            addItem(item);
        }
    }
}

void CustomScene::saveToXml(QDomDocument &doc, QDomElement &root)
{
    QDomElement sceneElement = doc.createElement("Scene");
    root.appendChild(sceneElement);

    for (QGraphicsItem *item : items())
    {
        QDomElement itemElement = doc.createElement("Item");
        itemElement.setAttribute("type", item->type());
        itemElement.setAttribute("x", item->x());
        itemElement.setAttribute("y", item->y());
        itemElement.setAttribute("width", item->boundingRect().width());
        itemElement.setAttribute("height", item->boundingRect().height());
        sceneElement.appendChild(itemElement);
    }
}

void CustomScene::loadFromXml(const QDomElement &root)
{
    QDomNodeList itemNodes = root.elementsByTagName("Item");
    for (int i = 0; i < itemNodes.count(); i++)
    {
        QDomElement itemElement = itemNodes.at(i).toElement();
        int type = itemElement.attribute("type").toInt();
        qreal x = itemElement.attribute("x").toDouble();
        qreal y = itemElement.attribute("y").toDouble();
        qreal width = itemElement.attribute("width").toDouble();
        qreal height = itemElement.attribute("height").toDouble();

        QGraphicsItem *item = nullptr;
        switch (type)
        {
        case QGraphicsRectItem::Type:
            item = new QGraphicsRectItem(x, y, width, height);
            break;
        case QGraphicsEllipseItem::Type:
            item = new QGraphicsEllipseItem(x, y, width, height);
            break;
        case QGraphicsLineItem::Type:
            item = new QGraphicsLineItem(x, y, width, height);
            break;
        case QGraphicsPolygonItem::Type:
            QPolygonF polygon;
            item = new QGraphicsPolygonItem(polygon);
            break;
        }

        if (item)
        {
            addItem(item);
        }
    }
}
