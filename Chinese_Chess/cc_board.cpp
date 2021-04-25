#include "cc_board.h"
#include "cc_grid.h"
#include "cc_piece.h"
#include "game.h"
#include "soldier.h"
#include "battery.h"
#include "chariot.h"
#include "guard.h"
#include "elephant.h"
#include "cavery.h"
#include "general.h"
#include <QDebug>
#include <QTimer>

extern Game *game;
CC_board::CC_board()
{
    initialBoard();
    initialBlue();
    initialRed();
}

CC_board::~CC_board()
{
    delete this;
}

// top half of the board
void CC_board::initialBlue()
{
    qDebug() << "[CC_board] start initialBlue()";
    CC_piece * newPiece;

    // setup the pieces for blue side
    // one general (make sure it's the first)
        newPiece = new general(0);
        newPiece->move(0,4);
        game->game_grid[0][4]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);
    // two guard (make sure these are 2nd and 3rd)
        newPiece = new guard(0);
        newPiece->move(0,3);
        game->game_grid[0][3]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);

        newPiece = new guard(0);
        newPiece->move(0,5);
        game->game_grid[0][5]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);
    // two elephant (make sure these are 4th and 5th)
        newPiece = new elephant(0);
        newPiece->move(0,2);
        game->game_grid[0][2]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);

        newPiece = new elephant(0);
        newPiece->move(0,6);
        game->game_grid[0][6]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);

    // 5 soldier
    for (int i = 0; i < 10; i +=2) {
        // construct new piece
        newPiece = new Soldier(0);// 0 is the blue side
        // move this piece to initial position
        newPiece->move(3, i);
        // assign this piece to a grid
        game->game_grid[3][i]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);
    }

    // two battery
        newPiece = new battery(0);
        newPiece->move(2,1);
        game->game_grid[2][1]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);

        newPiece = new battery(0);
        newPiece->move(2,7);
        game->game_grid[2][7]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);

    // two chariot
        newPiece = new chariot(0);
        newPiece->move(0,0);
        game->game_grid[0][0]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);

        newPiece = new chariot(0);
        newPiece->move(0,8);
        game->game_grid[0][8]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);



    // two cavery
        newPiece = new cavery(0);
        newPiece->move(0,1);
        game->game_grid[0][1]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);

        newPiece = new cavery(0);
        newPiece->move(0,7);
        game->game_grid[0][7]->updateMyPiece(newPiece);
        // add this piece to blue side list
        this->bluePieces.append(newPiece);
    qDebug() << "[CC_board] blue count: " << this->bluePieces.length();
    qDebug() << "[CC_board] finish initialBlue()";
}

// bottom half of the board
void CC_board::initialRed()
{
    qDebug() << "[CC_board] start initialRed()";
    CC_piece * newPiece;

    // setup the pieces for red side
    // one general
        newPiece = new general(1);
        newPiece->move(9,4);
        game->game_grid[9][4]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

    // two guard
        newPiece = new guard(1);
        newPiece->move(9,3);
        game->game_grid[9][3]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

        newPiece = new guard(1);
        newPiece->move(9,5);
        game->game_grid[9][5]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

    // two elephant
        newPiece = new elephant(1);
        newPiece->move(9,2);
        game->game_grid[9][2]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

        newPiece = new elephant(1);
        newPiece->move(9,6);
        game->game_grid[9][6]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);
    // 5 soldier
    for (int i = 0; i < 10; i +=2) {
        // construct new piece
        newPiece = new Soldier(1);// 1 is red side
        // set piece's position
        newPiece->move(6,i);
        // assign this piece to a grid
        game->game_grid[6][i]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

    }

    // two battery
        newPiece = new battery(1);
        newPiece->move(7,1);
        game->game_grid[7][1]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

        newPiece = new battery(1);
        newPiece->move(7,7);
        game->game_grid[7][7]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

    // two chariot
        newPiece = new chariot(1);
        newPiece->move(9,0);
        game->game_grid[9][0]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

        newPiece = new chariot(1);
        newPiece->move(9,8);
        game->game_grid[9][8]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);



    // two cavery
        newPiece = new cavery(1);
        newPiece->move(9,1);
        game->game_grid[9][1]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

        newPiece = new cavery(1);
        newPiece->move(9,7);
        game->game_grid[9][7]->updateMyPiece(newPiece);
        // add this piece to red side list
        this->redPieces.append(newPiece);

    qDebug() << "[CC_board] red count: " << this->redPieces.length();
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

            // add to the scene to show the grid.
            game->gameScene->addItem(new_grid);
        }
    }
    qDebug() << "[CC_board] finish initialBoard()";
}

void CC_board::resetBoard()
{
    qDebug() << "[cc_board] clean board";
    // put gird back, reset to origin value

    // put pieces back, reset to origin value


}
