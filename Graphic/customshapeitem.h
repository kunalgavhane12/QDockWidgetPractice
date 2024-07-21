#ifndef CUSTOMSHAPEITEM_H
#define CUSTOMSHAPEITEM_H

#include <QGraphicsItem>
#include <QPainter>

class CustomShapeItem : public QGraphicsItem {
public:
    enum ShapeType { Rectangle, Ellipse, Line, Triangle, RoundedRect, Square, Polygon };

    CustomShapeItem(ShapeType shape, const QRectF& rect);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    ShapeType shapeType;
    QRectF rect;

    void drawTriangle(QPainter* painter, const QRectF& rect);

    void drawPolygon(QPainter* painter, const QRectF& rect);
};

#endif // CUSTOMSHAPEITEM_H
