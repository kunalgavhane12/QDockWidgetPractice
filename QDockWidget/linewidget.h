#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>

class LineWidget : public QWidget {
    Q_OBJECT

public:
    explicit LineWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool dragging;
    bool resizing;
    QPoint startPos;
    QPoint endPos;
    QRect resizeHandleRect;
    static constexpr int HANDLE_SIZE = 8;

    bool isOnResizeHandle(const QPoint &pos) const;
    void updateResizeHandle();
};

#endif // LINEWIDGET_H
