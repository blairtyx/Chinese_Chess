#ifndef CC_PIECE_H
#define CC_PIECE_H

#include <QGraphicsPixmapItem>


class CC_piece :public QGraphicsPixmapItem
{
public:
    CC_piece(int side, QGraphicsItem *parent = 0);
    void pieceSetSide(int side);
    void pieceSetPosi(int x, int y);
    int getMyside();
    int getMyXPosi();
    int getMyYPosi();
    void reborn();
    virtual void selected(int x, int y);
    void move(int x, int y);
    void deselected();
    void died();
    bool checkAlive();


protected:
    // which side is this piece belongs to, 1 would be red, 0 would be blue
    int myside;
    int xPos;
    int yPos;
    bool alive;


};

#endif // CC_PIECE_H
