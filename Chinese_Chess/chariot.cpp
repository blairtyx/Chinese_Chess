#include "chariot.h"
#include <QDebug>
#include "game.h"
extern Game *game;

chariot::chariot(int side, QGraphicsItem *parent):CC_piece(side,parent)
{
    this->setImage();
    // add to scene
    this->setZValue(2);
    game->gameScene->addItem(this);

    qDebug() << "myside is " << this->myside;
}

void chariot::setImage()
{
    if (this->myside == 1) {
        setPixmap(QPixmap(":/image/soldier_test_2.png").scaled(27,27));
    }
    else if (this->myside == 0) {
        setPixmap(QPixmap(":/image/soldier_test.png").scaled(27,27));
    }

}

void chariot::selected(int x, int y)
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
    if (x_other>=0) {
        game->game_grid[x_other][y]->highlightColor();
    }

    x_other = x+1;
    while (x_other<10 && (!game->game_grid[x_other][y]->hasPiece)) {
        game->game_grid[x_other++][y]->highlightColor();
    }
    if (x_other <10) {
        game->game_grid[x_other][y]->highlightColor();
    }

    while (y_other>=0 && (!game->game_grid[x][y_other]->hasPiece)) {
        game->game_grid[x][y_other--]->highlightColor();
    }
    if (y_other>=0) {
        game->game_grid[x][y_other]->highlightColor();
    }

    y_other = y+1;

    while (y_other<9 && (!game->game_grid[x][y_other]->hasPiece)) {
        game->game_grid[x][y_other++]->highlightColor();
    }
    if (y_other<9) {
        game->game_grid[x][y_other]->highlightColor();
    }
}

