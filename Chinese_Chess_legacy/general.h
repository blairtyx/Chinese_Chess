#ifndef GENERAL_H
#define GENERAL_H

#include <QGraphicsPixmapItem>
#include "cc_piece.h"

class general: public CC_piece
{
public:
    general(int side, QGraphicsItem *parent = 0);
    void setImage();
    void selected(int x, int y);
};

#endif // GENERAL_H
