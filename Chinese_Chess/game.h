#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "cc_grid.h"
#include "cc_board.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    // Constructors
    Game(QWidget *parent = 0);
    // main methods
    void showWelcomeMenu();
    void drawCCBoard();
    void keyPressEvent(QKeyEvent *event);

    QGraphicsScene * gameScene;
    QList<QGraphicsItem *> gList;
    CC_board *chess_main_board;
    CC_grid * game_grid[10][9];
public slots:
    void areYouSure();
    void start();
    void guide();
    void notSure();

private:
    // member attributes


};

#endif // GAME_H
