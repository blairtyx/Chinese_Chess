#include "general.h"
#include <QDebug>
#include "game.h"

extern Game *game;

general::general(int side, QGraphicsItem *parent):CC_piece(side,parent)
{
    this->setImage();
    // add to scene
    this->setZValue(2);
    game->gameScene->addItem(this);

    qDebug() << "myside is " << this->myside;

}


void general::setImage()
{
    if (this->myside == 1) {
        setPixmap(QPixmap(":/image/general_blue_1.png").scaled(27,27));
    }
    else if (this->myside == 0) {
        setPixmap(QPixmap(":/image/general_red_1.png").scaled(27,27));
    }



}

void general::selected(int x, int y)
{
    qDebug() << "[Soldier]" << "x is "<< x << "y is " << y;


    //highlight this grid
    game->game_grid[x][y]->highlightColor();
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    if (y>3) {
        game->game_grid[x][y-1]->highlightColor();
    }
    if (y<5) {
        game->game_grid[x][y+1]->highlightColor();
    }
    // for blue side
    if (this->myside == 0) {
        if (x>0) {
            game->game_grid[x-1][y]->highlightColor();
        }
        if (x<2) {
            game->game_grid[x+1][y]->highlightColor();
        }

    }
    // for red side
    else if (this->myside == 1) {
        if (x>7) {
            game->game_grid[x-1][y]->highlightColor();
        }
        if (x<9) {
            game->game_grid[x+1][y]->highlightColor();
        }

    }
}



