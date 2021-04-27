#ifndef BATTERY_H
#define BATTERY_H

#include <QGraphicsPixmapItem>
#include "cc_piece.h"

class battery: public CC_piece
{
public:
    battery(int side, QGraphicsItem *parent = 0);
    void setImage();
    void selected(int x, int y);

};

#endif // BATTERY_H
