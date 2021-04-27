#include "myrect.h"
#include <QDebug>

MyRect::MyRect(int xSize, int ySize, int mode, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    setRect(0,0, xSize, ySize);
    if (mode == 1){
        // transparent mask
        setBrush(Qt::NoBrush);
    } else if (mode == 2) {
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::white);
        setBrush(brush);
    }


}

void MyRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event){
        // block the mouse click event
        qDebug() << "[MyRect] [MousePressed]";
        emit clicked();
    }
}
