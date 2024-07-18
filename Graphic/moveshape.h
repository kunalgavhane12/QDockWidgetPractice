#ifndef MOVESHAPE_H
#define MOVESHAPE_H

#include <QUndoCommand>
#include <QGraphicsItem>

class MoveShape : public QUndoCommand
{
public:
    MoveShape(QGraphicsItem *item, const QPointF &oldPos, const QPointF &newPos);

    void undo() override;

    void redo() override;

private:
    QGraphicsItem *m_item;
    QPointF m_oldPos;
    QPointF m_newPos;
};

#endif // MOVESHAPE_H
