#include "rectanglewidget.h"
#include <QPainter>
#include <QMouseEvent>

RectangleWidget::RectangleWidget(QWidget *parent) : QWidget(parent), dragging(false), resizing(false) {
//    setFixedSize(200, 200);
    rect = QRect(50, 50, 100, 100);
    updateResizeHandle();
}

void RectangleWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawRect(rect);
    painter.setBrush(Qt::black);
    painter.drawRect(resizeHandleRect);
}

void RectangleWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        if (isOnResizeHandle(event->pos()))
        {
            resizing = true;
        }
        else
        {
            dragging = true;
        }
        update();
    }
}

void RectangleWidget::mouseMoveEvent(QMouseEvent *event) {
    if (dragging)
    {
        rect.moveTo(event->pos());
        updateResizeHandle();
        update();
    }
    else if (resizing)
    {
        rect.setBottomRight(event->pos());
        updateResizeHandle();
        update();
    }
}

void RectangleWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
        resizing = false;
        update();
    }
}

bool RectangleWidget::isOnResizeHandle(const QPoint &pos) const {
    return resizeHandleRect.contains(pos);
}

void RectangleWidget::updateResizeHandle() {
    int x = rect.right() - HANDLE_SIZE / 2;
    int y = rect.bottom() - HANDLE_SIZE / 2;
    resizeHandleRect = QRect(x, y, HANDLE_SIZE, HANDLE_SIZE);
}
