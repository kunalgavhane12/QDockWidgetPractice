#include "circlewidget.h"

CircleWidget::CircleWidget(QWidget *parent)
    : QWidget(parent), dragging(false), resizing(false) {
//    setFixedSize(200, 200);
    circleRect = QRect(50, 50, 100, 100);
    updateResizeHandle();
}

void CircleWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawEllipse(circleRect);
    painter.setBrush(Qt::black);
    painter.drawRect(resizeHandleRect);
}

void CircleWidget::mousePressEvent(QMouseEvent *event) {
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

void CircleWidget::mouseMoveEvent(QMouseEvent *event) {
    if (dragging)
    {
        circleRect.moveTo(event->pos());
        updateResizeHandle();
        update();
    }
    else if (resizing)
    {
        circleRect.setBottomRight(event->pos());
        updateResizeHandle();
        update();
    }
}

void CircleWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
        resizing = false;
        update();
    }
}

bool CircleWidget::isOnResizeHandle(const QPoint &pos) const {
    return resizeHandleRect.contains(pos);
}

void CircleWidget::updateResizeHandle() {
    int x = circleRect.right() - HANDLE_SIZE / 2;
    int y = circleRect.bottom() - HANDLE_SIZE / 2;
    resizeHandleRect = QRect(x, y, HANDLE_SIZE, HANDLE_SIZE);
}
