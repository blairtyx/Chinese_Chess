#include "cc_grid.h"
#include <QDebug>



CC_grid::CC_grid(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    // create a rect
    setRect(0,0,27,27);
    brush.setStyle(Qt::Dense7Pattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
    // place it at layer -1
    //setZValue(-1);
    // set has piece as initial false
    this->hasPiece = false;

}

void CC_grid::CC_gridPosi(int xpos, int ypos)
{
    this->rowPosi = xpos;
    this->colPosi = ypos;
    qDebug() << "xpos is";
    qDebug() << xpos;
    qDebug() << "ypos is";
    qDebug() << ypos;
}

void CC_grid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event){
        brush.setColor(Qt::red);
        brush.setStyle(Qt::SolidPattern);
        setBrush(brush);
        qDebug() << "[in grid] MousePressed";
        qDebug() << this->rowPosi;
        qDebug() << this->colPosi;
    }
}


