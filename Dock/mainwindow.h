#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QRect>
#include <QLineF>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Shape {
        None,
        Rectangle,
        Line,
        Circle
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void setshapeRectangle();
    void setshapeLine();
    void setshapeCircle();
    void drawShapes(QPainter &painter);


private:
    Ui::MainWindow *ui;
    QImage *image;
    Shape shape;
    Shape selectedShape;

    QRect currentRect;
    QLineF currentLine;
    QRect currentCircle;
    QPoint dragStartPosition;
    bool resizing;
    QPoint resizeStartPos;
    QRect resizeStartRect;

    QList<QRect> rectangles;
    QList<QLineF> lines;
    QList<QRect> circles;


};

#endif // MAINWINDOW_H
