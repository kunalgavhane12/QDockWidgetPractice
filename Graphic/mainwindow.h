#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QToolBar>
#include <QPushButton>
#include <QUndoStack>
#include "shapebutton.h"
#include "customscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void zoomIn();
    void zoomOut();
    void undo();
    void redo();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    CustomScene *scene;

    ShapeButton *rectButton;
    ShapeButton *ellipseButton;
    ShapeButton *lineButton;
    ShapeButton *roundedRectangle;
    ShapeButton *squareDashed;
    ShapeButton *undoButton;
    ShapeButton *redoButton;
    qreal zoomFactor;
    QUndoStack *undoStack;

    void createToolbar();
};

#endif // MAINWINDOW_H
