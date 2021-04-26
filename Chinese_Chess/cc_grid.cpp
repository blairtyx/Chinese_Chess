#include "cc_grid.h"
#include "game.h"
#include <QDebug>


extern Game *game;
CC_grid::CC_grid(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    // create a rect
    setRect(0,0,27,27);
    setBrush(Qt::NoBrush);
    setPen(Qt::NoPen);
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
    // qDebug() << "xpos is" << xpos << "ypos is" << ypos;
}

void CC_grid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // selected this gird
    if (event){

        qDebug() << "[cc_grid] MousePressed" << this->xPos << this->yPos;
        // if no selected Piece
        if (game->selectedPiece == NULL) {
            qDebug() << "[cc_grid]" << " [selected 1st]"<< "has piece " << this->hasPiece;
            qDebug() << "[cc_grid]" << " [selected 1st]"<< "currentSide" << game->currentSide;


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
                qDebug() << "[cc_grid]" << " [deselected 1st]";
                // dehighlight everything
                this->myPiece->deselected();
                // set currentPiece as NULL
                game->selectedPiece = NULL;
            }
            // if selecting a highlighted grid
            else if(this->canMoveTo && this->myPiece != game->selectedPiece) {
                qDebug() << "[cc_grid]" << " [selected 2nd]"<< "selecting a highlighted grid";
                qDebug() << "[cc_grid]" << " [selected 2nd]"<< "canMoveTo " << this->canMoveTo;
                // check if this grid's piece belongs to the other side
                if ( this->hasPiece && this->myPiece->getMyside() != game->currentSide){
                    // mark this piece as died
                    this->myPiece->died();
                    // check if game is finished
                    int check = this->checkFinish();
                    if (check == 0) {
                        // red lose
                        qDebug() << "[cc_grid] [game finished] red lose game";
                        // clean board
                        game->showGameOverWindow(check);
                    } else if (check == 1) {
                        // blue lose
                        qDebug() << "[cc_grid] [game finished] blue lose game";
                        game->showGameOverWindow(check);
                    }
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

                    // flip the side
                    game->currentSide = (game->currentSide == 0) ? 1: 0;

                }
                // check if this piece belongs to the same side
                else if (this->hasPiece && this->myPiece->getMyside() == game->currentSide) {
                    qDebug() << "[cc_grid]"<< "[selected 2nd]" << "same side";
                }
                // if empty
                else if (!this->hasPiece) {
                    qDebug() << "[cc_grid]"<< "[selected 2nd]" << "empty grid";
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
    this->brush.setStyle(Qt::Dense5Pattern);
    this->setBrush(this->brush);
    // add this grid to highlighted grid list
    game->highlightedGrid.append(this);
    // set this grid as "canMoveTo" grid
    this->canMoveTo = true;

}

void CC_grid::dehighlightColor()
{

    this->setBrush(Qt::NoBrush);
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

void CC_grid::resetMyPiece()
{
    this->myPiece = NULL;
    this->hasPiece = false;
    this->canMoveTo = false;
}



int CC_grid::checkFinish()
{
    // check if one side have no piece to use on the board
    // for those who can move go across the river
    int deadCountRed = 0, deadCountBlue = 0;

    // start from the
    for (int i = 5; i < 16; i++) {
        if (!game->chess_main_board->redPieces[i]->checkAlive()) {
            deadCountRed++;
        }
        if (!game->chess_main_board->bluePieces[i]->checkAlive()) {
            deadCountBlue++;
        }
    }
    if (deadCountRed == 11) {
        // red all dead
        return 0;
    } else if (deadCountBlue == 11) {
        // blue all dead
        return 1;
    }
    // check if one side's general is "died"
    if (!game->chess_main_board->redPieces[0]->checkAlive()) {
        // red general is dead
        return 0;
    } else if (!game->chess_main_board->bluePieces[0]->checkAlive()) {
        // blue general is dead
        return 1;
    }
    // not finished yet
    return 2;
}






