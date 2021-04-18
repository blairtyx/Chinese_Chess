#ifndef CC_PIECE_H
#define CC_PIECE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class CC_piece :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CC_piece(QGraphicsItem * parent = 0);
};

#endif // CC_PIECE_H
