#include "cc_piece.h"
#include "game.h"
#include <QDebug>

extern Game *game;
CC_piece::CC_piece(int side, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    qDebug() << "[in CC_piece] generate a CC_piece" << " side is " << side;
    this->pieceSetSide(side);
    this->alive = true;
}


void CC_piece::pieceSetSide(int side)
{
    // which side is this piece belongs to, 1 would be red, 0 would be blue
    this->myside = side;
}

void CC_piece::pieceSetPosi(int x, int y)
{
    this->xPos = x;
    this->yPos = y;
}

int CC_piece::getMyside()
{
    return this->myside;
}

int CC_piece::getMyXPosi()
{
    return this->xPos;
}

int CC_piece::getMyYPosi()
{
    return this->yPos;
}

void CC_piece::selected(int x, int y)
{
    qDebug() << "[in CC_piece] selected";
    return;
}

void CC_piece::move(int x, int y)
{
    int offset = game->width()/2 - 27/2 - 27*4;
    this->setPos(offset + 27 * y, 1 + 27 * x);
    this->pieceSetPosi(x, y);
}

void CC_piece::deselected()
{
    // dehighlight every grid
    for (int i = 0; i < game->highlightedGrid.size(); i++) {
        game->highlightedGrid[i]->dehighlightColor();

    }
    // clear the highlighted list
    game->highlightedGrid.clear();
}

void CC_piece::died()
{
    this->alive = false;
}

bool CC_piece::checkAlive()
{
    if (this->alive){
        return true;
    } else {
        return false;
    }

}




