#include "cc_board.h"
#include "cc_grid.h"
#include "game.h"
#include <QDebug>

extern Game *game;
CC_board::CC_board()
{
    initialBoard();
    initialBlue();
    initialRed();
}

void CC_board::initialBlue()
{
    qDebug() << "[in CC_board] initial Blue";
}

void CC_board::initialRed()
{
    qDebug() << "[in CC_board] initial Red";
}

void CC_board::initialBoard()
{
    // get the offset of the grid
    int offset = game->width()/2 - 27/2 - 27*4;
    // set up the board with 10row 9col
    for(int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            CC_grid * new_grid = new CC_grid();
            game->game_grid[i][j] = new_grid;
            // initial value of position variable
            new_grid->CC_gridPosi(i,j);
            // set pos of the rect
            new_grid->setPos(offset+ 27*j, 1 + 27*i);

            // add to the scene
            game->gameScene->addItem(new_grid);

        }
    }
}
