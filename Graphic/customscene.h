#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QPaintEvent>
#include <QUndoCommand>
#include <QStack>
#include "shapebutton.h"
#include <QPainter>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CustomScene(QObject *parent = nullptr);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void paintEvent(QPaintEvent *event);

public slots:
    void cut();
    void copy();
    void paste();
    void undo();
    void redo();

private:
    bool isDragging;
    QGraphicsItem *draggedItem;
    QGraphicsItem *clipboard;
    QPointF dragStartPosition;
    QPointF lastMousePos;

    QStack<QGraphicsItem *> undoStack;
    QStack<QGraphicsItem *> redoStack;

};

#endif // CUSTOMSCENE_H
