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
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void zoomIn();
    void zoomOut();


private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    CustomScene *scene;

    ShapeButton *rectButton;
    ShapeButton *ellipseButton;
    ShapeButton *lineButton;
    ShapeButton *roundedRectangle;
    ShapeButton *squareDashed;
    ShapeButton *triangleButton;
    ShapeButton *polygonButton;
    qreal zoomFactor;
    QString currentFile;

    void createToolbar();
    void setCurrentFile(const QString &fileName);
};

#endif // MAINWINDOW_H
