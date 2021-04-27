#ifndef CHARIOT_H
#define CHARIOT_H

#include <QGraphicsPixmapItem>
#include "cc_piece.h"
class chariot:public CC_piece
{
public:
    chariot(int side, QGraphicsItem *parent = 0);
    void setImage();
    void selected(int x, int y);
};

#endif // CHARIOT_H
