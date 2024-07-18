#include "shapebutton.h"
#include <QDrag>
#include <QMimeData>

ShapeButton::ShapeButton(const QString &iconPath, ShapeType shapeType, QGraphicsScene *scene, QWidget *parent)
    : QPushButton(parent), m_shapeType(shapeType), m_scene(scene)
{
    setIcon(QIcon(iconPath));
    setIconSize(QSize(32, 32));
    setFixedSize(40, 40);
    setCheckable(true);
}

void ShapeButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(QString::number(m_shapeType));
        drag->setMimeData(mimeData);

        Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
    }
}
