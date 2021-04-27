#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "cc_grid.h"
#include "cc_board.h"
#include "cc_piece.h"

#include <QTimer>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    // Constructors
    Game(QWidget *parent = 0);
    // main methods
    void showWelcomeMenu();

    void showGameOverWindow(int side);// 0 is red, 1 is blue

    void cleanGridPiece();
    void initCCBoard(); // initialize a new board, with grids and pieces in it.

    void cleanWindow(); // remove everything from the window

    void keyPressEvent(QKeyEvent *event); // test method for key input

    QGraphicsScene * gameScene; // the main window to show items
    QList<QGraphicsItem *> gList; // contains all item that is currently shown in the scene(except for piece)
    CC_board *chess_main_board; // chess board, constructing the gird.
    CC_grid * game_grid[10][9]; //
    CC_piece * selectedPiece = NULL;
    QList <CC_grid *> highlightedGrid; // all highlighted grid
    CC_grid * gif_grid;
    int currentSide;
    QTimer *timer;
    int destx;
    int desty;
    int curr_x;
    int curr_y;
    bool selected;
    int seconds;
    QGraphicsTextItem *timeText;
public slots:
    void areYouSure();
    void start();
    void guide();
    void notSure();
    void restart();
    void close();
    void timer_pause();

    void timer_function();
private:

};

#endif // GAME_H
