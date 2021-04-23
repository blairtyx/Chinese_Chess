#ifndef ELEPHANT_H
#define ELEPHANT_H
#include <QGraphicsPixmapItem>
#include "cc_piece.h"

class elephant:public CC_piece
{
public:
    elephant(int side, QGraphicsItem *parent = 0);
    void setImage();
    void selected(int x, int y);
};

#endif // ELEPHANT_H
