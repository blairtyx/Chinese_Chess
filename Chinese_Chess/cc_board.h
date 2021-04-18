#ifndef CC_BOARD_H
#define CC_BOARD_H

#include <QGraphicsPixmapItem>

class CC_board : public QGraphicsPixmapItem
{
public:
    CC_board();
    void initialBlue();
    void initialRed();
    void initialBoard();

};

#endif // CC_BOARD_H
