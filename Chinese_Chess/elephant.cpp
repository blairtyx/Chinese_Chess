#include "elephant.h"
#include <QDebug>
#include "game.h"

extern Game *game;

elephant::elephant(int side, QGraphicsItem *parent):CC_piece(side,parent)
{
    this->setImage();
    // add to scene
    this->setZValue(2);
    game->gameScene->addItem(this);

    qDebug() << "myside is " << this->myside;

}


void elephant::setImage()
{
    if (this->myside == 1) {
        setPixmap(QPixmap(":/image/soldier_test_2.png").scaled(27,27));
    }
    else if (this->myside == 0) {
        setPixmap(QPixmap(":/image/soldier_test.png").scaled(27,27));
    }



}

void elephant::selected(int x, int y)
{
    qDebug() << "[elephant]" << "x is "<< x << "y is " << y;


    //highlight this grid
    game->game_grid[x][y]->highlightColor();
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    // for blue side
    if (this->myside == 0) {
        if (x>1&&y>1&&(!game->game_grid[x-1][y-1]->hasPiece)) {
            game->game_grid[x-2][y-2]->highlightColor();
        }
        if (x>1&&y<7&&(!game->game_grid[x-1][y+1]->hasPiece)) {
            game->game_grid[x-2][y+2]->highlightColor();
        }
        if (x<3&&y<7&&(!game->game_grid[x+1][y+1]->hasPiece)) {
            game->game_grid[x+2][y+2]->highlightColor();
        }
        if (x<3&&y>1&&(!game->game_grid[x+1][y-1]->hasPiece)) {
            game->game_grid[x+2][y-2]->highlightColor();
        }

    }
    // for red side
    else if (this->myside == 1) {
        if (x>6&&y>1&&(!game->game_grid[x-1][y-1]->hasPiece)) {
            game->game_grid[x-2][y-2]->highlightColor();
        }
        if (x>6&&y<7&&(!game->game_grid[x-1][y+1]->hasPiece)) {
            game->game_grid[x-2][y+2]->highlightColor();
        }
        if (x<8&&y<7&&(!game->game_grid[x+1][y+1]->hasPiece)) {
            game->game_grid[x+2][y+2]->highlightColor();
        }
        if (x<8&&y>1&&(!game->game_grid[x+1][y-1]->hasPiece)) {
            game->game_grid[x+2][y-2]->highlightColor();
        }

    }

}




