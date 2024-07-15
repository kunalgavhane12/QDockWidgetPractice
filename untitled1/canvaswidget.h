#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    void setDrawModeRectangle();
    void setDrawModeLine();
    void setDrawModeCircle();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    enum DrawMode { None, Rectangle, Line, Circle };
    DrawMode drawMode;
    QRect currentRect;
    QLineF currentLine;
    QRect currentCircle;
    QList<QRect> rectangles;
    QList<QRect> circles;
    QList<QLineF> lines;
    QPoint dragStartPosition;

    void drawShapes(QPainter &painter);

};

#endif // CANVASWIDGET_H
