#ifndef CC_BOARD_H
#define CC_BOARD_H


#include <QGraphicsPixmapItem>
#include "cc_piece.h"
#include <QTimer>

class CC_board : public QGraphicsPixmapItem
{
public:
    CC_board();
    void initialBlue();
    void initialRed();
    void initialBoard();
    void resetBoard();

    QList <CC_piece *> redPieces;
    QList <CC_piece *> bluePieces;
    QGraphicsPixmapItem *myBackGround;
};

#endif // CC_BOARD_H
