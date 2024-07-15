#include "linewidget.h"
#include <QPainter>
#include <QMouseEvent>

LineWidget::LineWidget(QWidget *parent) : QWidget(parent), dragging(false), resizing(false) {
//    setFixedSize(100, 100);
    updateResizeHandle();
}

void LineWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawLine(startPos, endPos);
    painter.setBrush(Qt::black);
    painter.drawRect(resizeHandleRect);
}

void LineWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        if (isOnResizeHandle(event->pos()))
        {
            resizing = true;
        }
        else
        {
            dragging = true;
            startPos = event->pos();
            endPos = startPos;
        }
        update();
    }
}

void LineWidget::mouseMoveEvent(QMouseEvent *event) {
    if (dragging)
    {
        endPos = event->pos();
        updateResizeHandle();
        update();
    }
    else if (resizing)
    {
        endPos = event->pos();
        updateResizeHandle();
        update();
    }
}

void LineWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
        resizing = false;
        update();
    }
}

bool LineWidget::isOnResizeHandle(const QPoint &pos) const {
    return resizeHandleRect.contains(pos);
}

void LineWidget::updateResizeHandle() {
    int x = endPos.x() - HANDLE_SIZE / 2;
    int y = endPos.y() - HANDLE_SIZE / 2;
    resizeHandleRect = QRect(x, y, HANDLE_SIZE, HANDLE_SIZE);
}
