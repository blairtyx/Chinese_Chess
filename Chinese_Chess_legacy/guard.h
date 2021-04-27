#ifndef GUARD_H
#define GUARD_H
#include <QGraphicsPixmapItem>
#include "cc_piece.h"

class guard:public CC_piece
{
public:
    guard(int side, QGraphicsItem *parent = 0);
    void setImage();
    void selected(int x, int y);
};

#endif // GUARD_H
