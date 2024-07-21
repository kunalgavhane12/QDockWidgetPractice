#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QJsonObject>
#include <QDomDocument>
#include <QDomElement>
#include <QList>
#include <QMimeData>
#include <QGraphicsPixmapItem>
#include "shapebutton.h"
#include "customview.h"

class CustomScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit CustomScene(QObject *parent = nullptr);

    void initializeDefaultShapes();
    void cut();
    void copy();
    void paste();
    void undo();
    void redo();
    void saveToJson(QJsonObject &json);
    void loadFromJson(const QJsonObject &json);
    void saveToXml(QDomDocument &doc, QDomElement &root);
    void loadFromXml(const QDomElement &root);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) ;

private:
    void addShapeItem(QGraphicsItem *item);

    QGraphicsRectItem *defaultRectItem;
    QGraphicsEllipseItem *defaultEllipseItem;
    QGraphicsLineItem *defaultLineItem;
    QGraphicsPolygonItem *defaultTriangleItem;
    QGraphicsRectItem *defaultRoundedRectItem;
    QGraphicsRectItem *defaultSquareRectItem;
    QGraphicsPolygonItem *defaultPolygonItem;

    QGraphicsItem *draggedItem;
    bool isDragging;
    QPointF dragStartPosition;
    QPointF lastMousePos;

    QList<QGraphicsItem *> undoStack;
    QList<QGraphicsItem *> redoStack;

    QGraphicsPixmapItem *draggedPixmapItem;
};

#endif // CUSTOMSCENE_H
