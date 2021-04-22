#include "cc_grid.h"
#include "game.h"
#include <QDebug>


extern Game *game;
CC_grid::CC_grid(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    // create a rect
    setRect(0,0,27,27);
    brush.setStyle(Qt::Dense1Pattern);
    brush.setColor(Qt::lightGray);
    setBrush(brush);
    // place it at layer -1
    //setZValue(-1);
    // set has piece as initial false
    this->hasPiece = false;
    this->canMoveTo = false;
}

void CC_grid::CC_gridPosi(int xpos, int ypos)
{
    this->xPos = xpos;
    this->yPos = ypos;
    qDebug() << "xpos is" << xpos << "ypos is" << ypos;
}

void CC_grid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // selected this gird
    if (event){

        qDebug() << "[cc_grid] MousePressed" << this->xPos << this->yPos;
        // if no selected Piece
        if (game->selectedPiece == NULL) {
            qDebug() << "[cc_grid]" << "No selected Piece, Selected one";
            qDebug() << "[cc_grid]" << "has piece " << this->hasPiece;
            qDebug() << "[cc_grid]" << "currentSide" << game->currentSide;


            // if there is a piece and is the right side.
            if (this->hasPiece && this->myPiece->getMyside() == game->currentSide) {
                // set this grid's piece as currentPiece
                game->selectedPiece = this->myPiece;

                // highlight this grid and it's target grid
                this->myPiece->selected(this->xPos, this->yPos);
            }
        }
        // already have one selected piece
        else {
            // if selecting the same piece
            if (this->myPiece == game->selectedPiece) {
                // dehighlight everything
                this->myPiece->deselected();
                // set currentPiece as NULL
                game->selectedPiece = NULL;
            }
            // if selecting a highlighted grid
            else if(this->canMoveTo && this->myPiece != game->selectedPiece) {
                qDebug() << "[cc_grid]" << "selecting a highlighted grid";
                qDebug() << "[cc_grid]" << "canMoveTo " << this->canMoveTo;
                // check if this grid's piece belongs to the other side
                if ( this->hasPiece && this->myPiece->getMyside() != game->currentSide){
                    // remove this piece from the scene
                    game->gameScene->removeItem(this->myPiece);
                    // update previous gird
                    int x = game->selectedPiece->getMyXPosi();
                    int y = game->selectedPiece->getMyYPosi();
                    game->game_grid[x][y]->removeMyPiece();
                    // remove this piece from this grid
                    this->removeMyPiece();
                    // move selected piece to this grid.
                    this->updateMyPiece(game->selectedPiece);
                    // move selected piece's position
                    this->myPiece->move(this->xPos, this->yPos);
                    // dehighlight everything
                    this->myPiece->deselected();
                    // set currentPiece as NULL
                    game->selectedPiece = NULL;
                    game->currentSide = (game->currentSide == 0) ? 1: 0;

                }
                // check if this piece belongs to the same side
                else if (this->hasPiece && this->myPiece->getMyside() == game->currentSide) {
                    qDebug() << "[cc_grid]" << "same side";
                }
                // if empty
                else if (!this->hasPiece) {
                    // update previous gird
                    int x = game->selectedPiece->getMyXPosi();
                    int y = game->selectedPiece->getMyYPosi();
                    game->game_grid[x][y]->removeMyPiece();
                    // update this grid
                    this->removeMyPiece();
                    // move selected piece to this gird
                    this->updateMyPiece(game->selectedPiece);
                    // move selected piece's position
                    this->myPiece->move(this->xPos, this->yPos);
                    // dehighlight everything
                    this->myPiece->deselected();
                    // set currentPiece as NULL
                    game->selectedPiece = NULL;
                    game->currentSide = (game->currentSide == 0) ? 1: 0;
                }


            }


        }




    }
}

void CC_grid::highlightColor()
{
    // set the color for this grid.
    this->brush.setColor(Qt::red);
    this->brush.setStyle(Qt::SolidPattern);
    this->setBrush(this->brush);
    // add this grid to highlighted grid list
    game->highlightedGrid.append(this);
    // set this grid as "canMoveTo" grid
    this->canMoveTo = true;

}

void CC_grid::dehighlightColor()
{
    this->brush.setColor(Qt::lightGray);
    this->brush.setStyle(Qt::Dense1Pattern);
    this->setBrush(this->brush);
    this->canMoveTo = false;
}


void CC_grid::updateMyPiece(CC_piece *piece)
{
    this->myPiece = piece;
    this->hasPiece = true;

}

void CC_grid::removeMyPiece()
{
    this->myPiece = NULL;
    this->hasPiece = false;
}




