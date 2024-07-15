#ifndef RECTANGLEWIDGET_H
#define RECTANGLEWIDGET_H

#include <QWidget>

class RectangleWidget : public QWidget {
    Q_OBJECT

public:
    explicit RectangleWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool dragging;
    bool resizing;
    QRect rect;
    QRect resizeHandleRect;
    static constexpr int HANDLE_SIZE = 8;

    bool isOnResizeHandle(const QPoint &pos) const;
    void updateResizeHandle();
};

#endif // RECTANGLEWIDGET_H
