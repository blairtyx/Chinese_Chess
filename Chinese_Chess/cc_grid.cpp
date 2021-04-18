#include "cc_grid.h"
#include "game.h"
#include <QDebug>


extern Game *game;
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
    qDebug() << "xpos is" << xpos << "ypos is" << ypos;
}

void CC_grid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event){
        this->brush.setColor(Qt::red);
        this->brush.setStyle(Qt::SolidPattern);
        this->setBrush(this->brush);
        qDebug() << "[in grid] MousePressed" << this->rowPosi << this->colPosi;
        game->game_grid[this->rowPosi + 1][this->colPosi +1]->updateColor(Qt::black);

    }
}

void CC_grid::updateColor(QColor c)
{
    this->brush.setColor(c);
    this->brush.setStyle(Qt::SolidPattern);
    this->setBrush(this->brush);
}




