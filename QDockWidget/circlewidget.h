#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class CircleWidget : public QWidget {
    Q_OBJECT

public:
    explicit CircleWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool dragging;
    bool resizing;
    QRect circleRect;
    QRect resizeHandleRect;
    static constexpr int HANDLE_SIZE = 8;

    bool isOnResizeHandle(const QPoint &pos) const;

    void updateResizeHandle();
};

#endif // CIRCLEWIDGET_H
