#include "moveshape.h"

MoveShape::MoveShape(QGraphicsItem *item, const QPointF &oldPos, const QPointF &newPos)
    : m_item(item), m_oldPos(oldPos), m_newPos(newPos)
{
    setText("Move Shape");
}

void MoveShape::undo()
{
    m_item->setPos(m_oldPos);
}

void MoveShape::redo()
{
    m_item->setPos(m_newPos);
}
