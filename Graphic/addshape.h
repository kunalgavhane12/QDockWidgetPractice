#ifndef ADDSHAPE_H
#define ADDSHAPE_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <QGraphicsItem>

class AddShape : public QUndoCommand
{
public:
    AddShape(QGraphicsScene *scene, QGraphicsItem *item);

    void undo() override;

    void redo() override;

private:
    QGraphicsScene *m_scene;
    QGraphicsItem *m_item;
};


#endif // ADDSHAPE_H
