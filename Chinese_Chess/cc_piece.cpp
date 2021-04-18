#include "cc_piece.h"
#include <QDebug>
CC_piece::CC_piece(QGraphicsItem * parent):QGraphicsPixmapItem(parent)
{
    qDebug() << "[in CC_piece] generate a CC_piece";
}
