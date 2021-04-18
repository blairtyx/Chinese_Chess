#include "myrect.h"
#include <QDebug>

MyRect::MyRect(int xSize, int ySize, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    setRect(0,0, xSize, ySize);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);

}

void MyRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event){
        // block the mouse click event
        qDebug() << "[In myRect] MousePressed";
        emit clicked();
    }
}
