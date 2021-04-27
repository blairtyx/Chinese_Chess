#ifndef SOLDIER_H
#define SOLDIER_H

#include <QGraphicsPixmapItem>
#include "cc_piece.h"

class Soldier : public CC_piece
{
public:
    Soldier(int side, QGraphicsItem *parent = 0);
    void setImage();
    void selected(int x, int y);
};

#endif // SOLDIER_H
