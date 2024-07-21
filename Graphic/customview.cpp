#include "customview.h"

CustomView::CustomView(QWidget *parent) : QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);
}

void CustomView::wheelEvent(QWheelEvent *event)
{
//    setTransformationAnchor(AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);
    double scalefactor = 1.5;

    if(event->modifiers() & Qt::ControlModifier)
    {
        if(event->delta() > 0)
        {
           scale(scalefactor,scalefactor);
        }
        else
        {
            scale(1/scalefactor,1/scalefactor);
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }

}
