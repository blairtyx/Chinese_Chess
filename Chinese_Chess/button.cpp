#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QtEvents>
#include <QDebug>

Button::Button(QString name, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    // show the rect button

    setRect(0,0, 65,30);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    // show the text of this button
    text = new QGraphicsTextItem(name, this);
    text->setDefaultTextColor(Qt::black);
    text->setPos(rect().width() /2 - text->boundingRect().size().width()/2,
                 rect().height()/2 - text->boundingRect().size().height()/2);

    // accept hover of mouse
    setAcceptHoverEvents(true);

}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event){
        qDebug() << this->text->toPlainText();
        qDebug() << "[in button] MousePressed";
        emit clicked();
    }
}

void Button::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter){
        qDebug() << this->text->toPlainText();
        qDebug() << "hhhhh";
    }
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (event){
      qDebug() << this->text->toPlainText();
      qDebug() << "[in button] hover_enter";
    }
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (event){
        qDebug() << this->text->toPlainText();
        qDebug() << "[in button] hover_esc";
    }
}
