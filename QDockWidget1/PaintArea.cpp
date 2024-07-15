#include "PaintArea.h"
#include <QPainter>
#include <QMouseEvent>

PaintArea::PaintArea(QWidget *parent)
    : QWidget(parent), selectedShape(-1), lineStart(QPoint(-1, -1)), lineEnd(QPoint(-1, -1)) {
    shapes.append(QRect(50, 50, 100, 100));
    shapes.append(QRect(200, 200, 100, 100));
}

void PaintArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Draw shapes
    painter.setBrush(Qt::white);
    for (const QRect& shape : shapes) {
        painter.drawRect(shape);
    }

    // Draw lines
    painter.setPen(Qt::black);
    for (const QPair<QPoint, QPoint>& line : lines) {
        painter.drawLine(line.first, line.second);
    }

    // Draw current line
    if (lineStart != QPoint(-1, -1) && lineEnd != QPoint(-1, -1)) {
        painter.drawLine(lineStart, lineEnd);
    }
}

void PaintArea::mousePressEvent(QMouseEvent *event) {
    QRect shape = findShapeAt(event->pos());
    if (!shape.isNull()) {
        selectedShape = shapes.indexOf(shape);
        lineStart = shape.center();
    } else {
        selectedShape = -1;
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event) {
    if (selectedShape != -1) {
        lineEnd = event->pos();
        update();
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event) {
    QRect shape = findShapeAt(event->pos());
    if (!shape.isNull() && selectedShape != -1 && selectedShape != shapes.indexOf(shape)) {
        lineEnd = shape.center();
        lines.append(qMakePair(lineStart, lineEnd));
    }
    lineStart = QPoint(-1, -1);
    lineEnd = QPoint(-1, -1);
    selectedShape = -1;
    update();
}

QRect PaintArea::findShapeAt(const QPoint& point) const {
    for (const QRect& shape : shapes) {
        if (shape.contains(point)) {
            return shape;
        }
    }
    return QRect();
}
