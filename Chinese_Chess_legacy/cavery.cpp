#include "cavery.h"
#include <QDebug>
#include "game.h"

extern Game *game;

cavery::cavery(int side, QGraphicsItem *parent):CC_piece(side,parent)
{
    this->setImage();
    // add to scene
    this->setZValue(2);
    game->gameScene->addItem(this);

    qDebug() << "myside is " << this->myside;

}


void cavery::setImage()
{
    if (this->myside == 1) {
        setPixmap(QPixmap(":/image/horse_red_1.png").scaled(27,27));
    }
    else if (this->myside == 0) {
        setPixmap(QPixmap(":/image/horse_blue_1.png").scaled(27,27));
    }



}

void cavery::selected(int x, int y)
{
    qDebug() << "[elephant]" << "x is "<< x << "y is " << y;


    //highlight this grid
    game->game_grid[x][y]->highlightColor();
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    if (x>1&&(!game->game_grid[x-1][y]->hasPiece)) {
        if (y>0) {
            game->game_grid[x-2][y-1]->highlightColor();
        }
        if (y<8) {
            game->game_grid[x-2][y+1]->highlightColor();
        }
    }

    if (x<8&&(!game->game_grid[x+1][y]->hasPiece)) {
        if (y>0) {
            game->game_grid[x+2][y-1]->highlightColor();
        }
        if (y<8) {
            game->game_grid[x+2][y+1]->highlightColor();
        }
    }

    if (y>1&&(!game->game_grid[x][y-1]->hasPiece)) {
        if (x>0) {
            game->game_grid[x-1][y-2]->highlightColor();
        }
        if (x<9) {
            game->game_grid[x+1][y-2]->highlightColor();
        }
    }

    if (y<7&&(!game->game_grid[x][y+1]->hasPiece)) {
        if (x>0) {
            game->game_grid[x-1][y+2]->highlightColor();
        }
        if (x<9) {
            game->game_grid[x+1][y+2]->highlightColor();
        }
    }

}

