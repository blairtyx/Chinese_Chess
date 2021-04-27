#include "battery.h"
#include <QDebug>
#include "game.h"
extern Game *game;

battery::battery(int side, QGraphicsItem *parent):CC_piece(side,parent)
{
    this->setImage();
    // add to scene
    this->setZValue(2);
    game->gameScene->addItem(this);

    qDebug() << "myside is " << this->myside;
}

void battery::setImage()
{
    if (this->myside == 1) {
        setPixmap(QPixmap(":/image/cannon_red_1.png").scaled(27,27));
    }
    else if (this->myside == 0) {
        setPixmap(QPixmap(":/image/cannon_blue_1.png").scaled(27,27));
    }
}

void battery::selected(int x, int y)
{
    qDebug() << "[battery]" << "x is "<< x << "y is " << y;
    int x_other = x-1;
    int y_other = y-1;
    //highlight this grid
    game->game_grid[x][y]->highlightColor();
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    // for red side
    while (x_other>=0&& (!game->game_grid[x_other][y]->hasPiece)) {
        game->game_grid[x_other--][y]->highlightColor();
    }
    x_other--;
    while (x_other>=0) {
        if (game->game_grid[x_other][y]->hasPiece) {
            game->game_grid[x_other][y]->highlightColor();
            break;
        }
        x_other--;
    }

    x_other = x+1;
    while (x_other<10 && (!game->game_grid[x_other][y]->hasPiece)) {
        game->game_grid[x_other++][y]->highlightColor();
    }
    x_other++;
    while (x_other<10) {
        if (game->game_grid[x_other][y]->hasPiece) {
            game->game_grid[x_other][y]->highlightColor();
            break;
        }
        x_other++;
    }

    while (y_other>=0 && (!game->game_grid[x][y_other]->hasPiece)) {
        game->game_grid[x][y_other--]->highlightColor();
    }
    y_other--;
    while (y_other>=0) {
        if (game->game_grid[x][y_other]->hasPiece) {
            game->game_grid[x][y_other]->highlightColor();
            break;
        }
        y_other--;
    }

    y_other = y+1;

    while (y_other<9 && (!game->game_grid[x][y_other]->hasPiece)) {
        game->game_grid[x][y_other++]->highlightColor();
    }
    y_other++;
    while (y_other<9) {
        if (game->game_grid[x][y_other]->hasPiece) {
            game->game_grid[x][y_other]->highlightColor();
            break;
        }
        y_other++;
    }
}
