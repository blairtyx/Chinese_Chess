#include "guard.h"
#include <QDebug>
#include "game.h"

extern Game *game;

guard::guard(int side, QGraphicsItem *parent):CC_piece(side,parent)
{
    this->setImage();
    // add to scene
    this->setZValue(2);
    game->gameScene->addItem(this);

    qDebug() << "myside is " << this->myside;

}


void guard::setImage()
{
    if (this->myside == 1) {
        setPixmap(QPixmap(":/image/advisor_red_1.png").scaled(27,27));
    }
    else if (this->myside == 0) {
        setPixmap(QPixmap(":/image/advisor_blue_1.png").scaled(27,27));
    }



}

void guard::selected(int x, int y)
{
    qDebug() << "[guard]" << "x is "<< x << "y is " << y;


    //highlight this grid
    game->game_grid[x][y]->highlightColor();
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    // for blue side
    if (this->myside == 0) {
        if (x>0&&y>3) {
            game->game_grid[x-1][y-1]->highlightColor();
        }
        if (x>0&&y<5) {
            game->game_grid[x-1][y+1]->highlightColor();
        }
        if (x<2&&y<5) {
            game->game_grid[x+1][y+1]->highlightColor();
        }
        if (x<2&&y>3) {
            game->game_grid[x+1][y-1]->highlightColor();
        }

    }
    // for red side
    else if (this->myside == 1) {
        if (x>7&&y>3) {
            game->game_grid[x-1][y-1]->highlightColor();
        }
        if (x>7&&y<5) {
            game->game_grid[x-1][y+1]->highlightColor();
        }
        if (x<9&&y<5) {
            game->game_grid[x+1][y+1]->highlightColor();
        }
        if (x<9&&y>3) {
            game->game_grid[x+1][y-1]->highlightColor();
        }
    }

}



