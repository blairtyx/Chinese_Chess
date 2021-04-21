#include "cc_board.h"
#include "cc_grid.h"
#include "cc_piece.h"
#include "game.h"
#include "soldier.h"
#include <QDebug>

extern Game *game;
CC_board::CC_board()
{
    initialBoard();
    initialBlue();
    initialRed();
}

// top half of the board
void CC_board::initialBlue()
{
    qDebug() << "[CC_board] start initialBlue()";
    CC_piece * newPiece;

    // setup the pieces for blue side
    // 5 soldier
    for (int i = 0; i < 10; i +=2) {
        // construct new piece
        newPiece = new Soldier(0);// 0 is the blue side
        // move this piece to initial position
        newPiece->move(3, i);
        // assign this piece to a grid
        game->game_grid[3][i]->updateMyPiece(newPiece);
    }
    // two advisor

    // one king/general

    // two cannon

    // two Chariot

    // two elephant

    // two horse



    qDebug() << "[CC_board] finish initialBlue()";
}

// bottom half of the board
void CC_board::initialRed()
{
    qDebug() << "[CC_board] start initialRed()";
    CC_piece * newPiece;

    // setup the pieces for red side
    // 5 soldier
    for (int i = 0; i < 10; i +=2) {
        // construct new piece
        newPiece = new Soldier(1);// 1 is red side
        // set piece's position
        newPiece->move(6,i);
        // assign this piece to a grid
        game->game_grid[6][i]->updateMyPiece(newPiece);
    }
    // two advisor

    // one king/general

    // two cannon

    // two Chariot

    // two elephant

    // two horse




    qDebug() << "[CC_board] finish initialRed()";

}

void CC_board::initialBoard()
{
    // get the offset of the grid
    int offset = game->width()/2 - 27/2 - 27*4;

    // set up the board with 10row 9col grids.
    for(int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            CC_grid * new_grid = new CC_grid();
            game->game_grid[i][j] = new_grid;
            // initial value of position variable
            new_grid->CC_gridPosi(i,j);
            // set pos of the rect
            new_grid->setPos(offset+ 27*j, 1 + 27*i);

            // [test only] add to the scene to show the grid.
            game->gameScene->addItem(new_grid);

        }
    }
    qDebug() << "[CC_board] finish initialBoard()";
}
