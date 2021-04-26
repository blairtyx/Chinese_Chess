#include "soldier.h"
#include <QDebug>
#include "game.h"

extern Game *game;



Soldier::Soldier(int side, QGraphicsItem *parent):CC_piece(side,parent)
{
    this->setImage();
    // add to scene
    this->setZValue(2);
    game->gameScene->addItem(this);

    qDebug() << "myside is " << this->myside;

}


void Soldier::setImage()
{
    if (this->myside == 1) {
        setPixmap(QPixmap(":/image/soldier_blue_1.png").scaled(27,27));
    }
    else if (this->myside == 0) {
        setPixmap(QPixmap(":/image/soldier_red_1.png").scaled(27,27));
    }



}

void Soldier::selected(int x, int y)
{
    qDebug() << "[Soldier]" << "x is "<< x << "y is " << y;


    //highlight this grid
    game->game_grid[x][y]->highlightColor();
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    // for red side
    if (this->myside == 1) {
        // if haven't pass the river
        if (x < 5 && x >=0){
            if (y > 0 && y < 8){
                game->game_grid[x][y-1]->highlightColor();
                game->game_grid[x][y+1]->highlightColor();
            } else if (y == 0){
                game->game_grid[x][y+1]->highlightColor();
            } else if (y == 8) {
                game->game_grid[x][y-1]->highlightColor();
            }
        }
        if (x > 0) {
            game->game_grid[x-1][y]->highlightColor();
        }

    }
    // for blue side
    else if (this->myside == 0) {
        // if haven't pass the river
        if (x <9) {
            game->game_grid[x + 1][y]->highlightColor();
        }
        if (x > 4 && x <= 9) {
            if (y > 0 && y<8){
                game->game_grid[x][y-1]->highlightColor();
                game->game_grid[x][y+1]->highlightColor();
            } else if (y == 0) {
                game->game_grid[x][y+1]->highlightColor();
            } else if (y == 8) {
                game->game_grid[x][y-1]->highlightColor();
            }
        }
    }

}


