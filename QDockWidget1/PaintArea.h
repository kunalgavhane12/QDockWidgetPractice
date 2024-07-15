#ifndef PaintArea_H
#define PaintArea_H

#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QVector>

class PaintArea : public QWidget {
    Q_OBJECT

public:
    PaintArea(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<QRect> shapes;
    QVector<QPair<QPoint, QPoint>> lines;
    int selectedShape;
    QPoint lineStart;
    QPoint lineEnd;

    QRect findShapeAt(const QPoint& point) const;
};

#endif // PaintArea_H
