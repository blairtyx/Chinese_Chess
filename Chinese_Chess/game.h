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

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    // Constructors
    Game(QWidget *parent = 0);
    // main methods
    void showWelcomeMenu();

    void initCCBoard(); // initialize a new board, with grids and pieces in it.

    void cleanWindow(); // remove everything from the window

    void redrawCCBoard(); // add the board back to the scene

    void keyPressEvent(QKeyEvent *event); // test method for key input

    QGraphicsScene * gameScene; // the main window to show items
    QList<QGraphicsItem *> gList; // contains all item that is currently shown in the scene(except for piece)
    CC_board *chess_main_board; // chess board, containing the grid and pieces.
    CC_grid * game_grid[10][9]; //
    CC_piece * selectedPiece = NULL;
    QList <CC_grid *> highlightedGrid; // all highlighted grid
    int currentSide;


public slots:
    void areYouSure();
    void start();
    void guide();
    void notSure();

private:
    // member attributes


};

#endif // GAME_H
