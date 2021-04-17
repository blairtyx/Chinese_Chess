#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    // Constructors
    Game(QWidget *parent = 0);
    // main methods
    void showWelcomeMenu();
    void drawCCBoard();


public slots:

    void start();
    void guide();

private:
    // member attributes
    QGraphicsScene * gameScene;
    QList<QGraphicsItem *> gList;

};

#endif // GAME_H
