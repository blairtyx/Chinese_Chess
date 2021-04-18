#ifndef CC_GRID_H
#define CC_GRID_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QBrush>
#include "cc_piece.h"



class CC_grid : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    CC_grid(QGraphicsItem *parent = 0);
    void CC_gridPosi(int xpos, int ypos);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    QBrush brush;
    bool hasPiece;
    int rowPosi;
    int colPosi;
    // CC_piece * myPiece;

};

#endif // CC_GRID_H
