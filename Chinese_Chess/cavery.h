#ifndef CAVERY_H
#define CAVERY_H

#include <QGraphicsPixmapItem>
#include "cc_piece.h"

class cavery:public CC_piece
{
public:
    cavery(int side, QGraphicsItem *parent = 0);
    void setImage();
    void selected(int x, int y);
};

#endif // CAVERY_H
