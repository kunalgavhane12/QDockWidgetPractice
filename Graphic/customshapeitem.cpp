#include "customshapeitem.h"


CustomShapeItem::CustomShapeItem(ShapeType shape, const QRectF &rect)
    : shapeType(shape), rect(rect) {}

QRectF CustomShapeItem::boundingRect() const {
    return rect;
}

void CustomShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);

    switch (shapeType) {
    case Rectangle:
        painter->setBrush(Qt::blue);
        painter->drawRect(rect);
        break;
    case Ellipse:
        painter->setBrush(Qt::green);
        painter->drawEllipse(rect);
        break;
    case Line:
        painter->setPen(QPen(Qt::red, 2));
        painter->drawLine(rect.topLeft(), rect.bottomRight());
        break;
    case Triangle:
        painter->setBrush(Qt::yellow);
        drawTriangle(painter, rect);
        break;
    case RoundedRect:
        painter->setBrush(Qt::cyan);
        painter->drawRoundedRect(rect, 10, 10);
        break;
    case Square:
        painter->setBrush(Qt::magenta);
        painter->drawRect(rect);
        break;
    case Polygon:
        painter->setBrush(Qt::darkGreen);
        drawPolygon(painter, rect);
        break;
    }
}

void CustomShapeItem::drawTriangle(QPainter *painter, const QRectF &rect) {
    QPolygonF triangle;
    triangle << rect.topLeft() << rect.bottomLeft() << QPointF(rect.right(), rect.center().y());
    painter->drawPolygon(triangle);
}

void CustomShapeItem::drawPolygon(QPainter *painter, const QRectF &rect) {
    QPolygonF polygon;
    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft();
    painter->drawPolygon(polygon);
}
