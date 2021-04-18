#ifndef MYRECT_H
#define MYRECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>


class MyRect: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    // Constructor
    MyRect(int xSize, int ySize, QGraphicsItem * parent = NULL);

    // main method
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QBrush brush;
signals:
    void clicked();

};

#endif // MYRECT_H
