#include "addshape.h"

AddShape::AddShape(QGraphicsScene *scene, QGraphicsItem *item)
    : m_scene(scene), m_item(item)
{
    setText("Add Shape");
}

void AddShape::undo()
{
    m_scene->removeItem(m_item);
}

void AddShape::redo()
{
    m_scene->addItem(m_item);
}
