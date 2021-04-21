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
    void highlightColor();
    void dehighlightColor();

    void updateMyPiece(CC_piece * piece);
    void removeMyPiece();

private:
    QBrush brush;
    bool hasPiece;
    int xPos;
    int yPos;
    CC_piece * myPiece;
    bool canMoveTo;

};

#endif // CC_GRID_H
