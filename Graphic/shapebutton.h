#ifndef SHAPEBUTTON_H
#define SHAPEBUTTON_H

#include <QPushButton>
#include <QGraphicsScene>
#include <QMouseEvent>

class ShapeButton : public QPushButton
{
    Q_OBJECT

public:
    enum ShapeType { Rectangle,
                     Ellipse,
                     Line,
                     SquareRectangle,
                     RoundedRectangle,
                     TriangleRectangle,
                     Polygon };

    ShapeButton(const QString &iconPath, ShapeType shapeType, QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    ShapeType m_shapeType;
    QGraphicsScene *m_scene;
};

#endif // SHAPEBUTTON_H
