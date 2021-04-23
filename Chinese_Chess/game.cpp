#include "game.h"
#include "button.h"
#include "cc_board.h"
#include "myrect.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QBrush>
#include <QDebug>
#include <QApplication>

Game::Game(QWidget *parent): QGraphicsView(parent)
{
    // create a scene
    gameScene = new QGraphicsScene(this);


    // set size of the scene
    gameScene->setSceneRect(0,0,480, 272);
    setFixedSize(480,272);
    // remove scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // set the scene
    setScene(gameScene);

    // background part
    QBrush bg_brush;
    bg_brush.setStyle(Qt::SolidPattern);
    bg_brush.setColor(Qt::white);
    setBackgroundBrush(bg_brush);
}

void Game::showWelcomeMenu()
{
    // Show the Game name
    QGraphicsTextItem *nameText = new QGraphicsTextItem("Chinese Chess");
    QFont nameFont("arial", 30);
    nameText->setFont(nameFont);
    nameText->setDefaultTextColor(Qt::black);
    nameText->setPos(width()/2 - nameText->boundingRect().width()/2, 50);
    gameScene->addItem(nameText);
    gList.append(nameText);

    // Show the author
    QGraphicsTextItem *auText = new QGraphicsTextItem("L & X");
    QFont auFont("arial", 10);
    auText->setFont(auFont);
    auText->setDefaultTextColor(Qt::black);
    auText->setPos(width()/2 - auText->boundingRect().width()/2, nameText->y() + nameText->boundingRect().height() + 10);
    gameScene->addItem(auText);
    gList.append(auText);

    // Show the play button
    Button *play_bt = new Button("2P");
    play_bt->setPos(width()/2 - play_bt->boundingRect().width()/2 -80,
                    nameText->y() + nameText->boundingRect().height() + 50);
    connect(play_bt, SIGNAL(clicked()), this, SLOT(start()));
    gameScene->addItem(play_bt);
    gList.append(play_bt);


    // Show the Guide button
    Button *guide_bt = new Button("Guide");
    guide_bt->setPos(width()/2 - guide_bt->boundingRect().width()/2,
                    nameText->y() + nameText->boundingRect().height() + 50);
    connect(guide_bt, SIGNAL(clicked()), this, SLOT(guide()));
    gameScene->addItem(guide_bt);
    gList.append(guide_bt);


    // Show the quit button
    Button *quit_bt = new Button("Quit");
    quit_bt->setPos(width()/2 - quit_bt->boundingRect().width()/2 + 80,
                    nameText->y() + nameText->boundingRect().height() + 50);
    connect(quit_bt, SIGNAL(clicked()), this, SLOT(areYouSure()));
    gameScene->addItem(quit_bt);
    gList.append(quit_bt);
}

void Game::showGameOverWindow(int side)
{
    // 0 is red, 1 is blue

    // freeze current scene
    int offset = width()/2 - 27/2 - 27*4;
    MyRect *blankMask = new MyRect(243, 272, 1);// transparent mask
    blankMask->setZValue(3);
    blankMask->setPos(offset, 0);
    gameScene->addItem(blankMask);
    gList.append(blankMask);

    // show result text
    QGraphicsTextItem * resultText;
    if (side == 0 ){
        resultText = new QGraphicsTextItem("Red lost");
    } else {
        resultText = new QGraphicsTextItem("Blue lost");
    }
    QFont resultFont("arial", 15);
    resultText->setFont(resultFont);
    resultText->setDefaultTextColor(Qt::red);
    resultText->setPos(offset/2 - resultText->boundingRect().width()/2,
                       height()/2 - resultText->boundingRect().height()/2);
    gameScene->addItem(resultText);
    gList.append(resultText);
    // show restart button (not implemented)
    Button *restart_bt = new Button("restart");
    restart_bt->setPos(offset/2 - restart_bt->boundingRect().width()/2,
                       resultText->y() + resultText->boundingRect().height() + restart_bt->boundingRect().height());
    connect(restart_bt, SIGNAL(clicked()), this, SLOT(restart()));
    gameScene->addItem(restart_bt);
    gList.append(restart_bt);
    qDebug() << "[game]"<< " [Game Over]" << side;
}

void Game::cleanGridPiece()
{
    // remove grid from the scene
    for(int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            this->gameScene->removeItem(this->game_grid[i][j]);
            qDebug() << "[game]"<< " [Game Over]" << "[remove grid]" << i << j;
        }
    }

    // remove pieces from the scene
    qDebug() << "[game]"<< " [Game Over]" << "[remove piece]" << "red";
    for(int i = 0, n = this->chess_main_board->redPieces.length(); i<n; i++) {
        this->gameScene->removeItem(this->chess_main_board->redPieces[i]);
        qDebug() << "[game]"<< " [Game Over]" << "[remove piece]" << i;
    }
    qDebug() << "[game]"<< " [Game Over]" << "[remove piece]" << "blue";
    for(int i = 0, n = this->chess_main_board->bluePieces.length(); i<n; i++) {
        this->gameScene->removeItem(this->chess_main_board->bluePieces[i]);
        qDebug() << "[game]"<< " [Game Over]" << "[remove piece]" << i;
    }
    // clean pause button (not implemented)

}


void Game::initCCBoard()
{
    chess_main_board = new CC_board();
    // set current side as 1, red first;
    this->currentSide = 1;

}

void Game::cleanWindow()
{
    // remove from scene
    for (int i = 0, N = gList.size(); i < N ; ++i) {
        gameScene->removeItem(gList[i]);
    }
    // remove from gList
    this->gList.clear();

}

void Game::redrawCCBoard()
{
    // redraw the board after we select the piece

    // add the grid back to scene
    for (int i = 0; i<10 ; ++i){
        for(int j= 0; j<10; ++j) {

            this->gameScene->addItem(this->game_grid[i][j]); // add to scene to show the item
            this->gList.append(this->game_grid[i][j]); // add to gList to keep item trackable

        }
    }

    // add additional buttons (like pause and timer)
}

// can close the application with 'ESC' key
void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape){
        QApplication::quit();
    }
}



void Game::start()
{
    qDebug() << "[game] [start]";
    // refresh the scene, remove every thing from the scene for now
    cleanWindow();
    // initialize the chessboard, make new board and store them in game->chess_main_board;
    initCCBoard();
}

void Game::guide()
{
    // would show a dedicated page for user guide

    qDebug() << "[game] [guide]";
}

// pop after the quit button is pressed.
void Game::areYouSure()
{
    // pop a window
    MyRect *areYouSure = new MyRect(250, 120, 2);// opaque background
    // uper layer than the main window
    areYouSure->setZValue(2);
    areYouSure->setPos(width()/2 - areYouSure->boundingRect().width()/2,
                       height()/2 - areYouSure->boundingRect().height()/2);

    gameScene->addItem(areYouSure);
    gList.append(areYouSure);
    // yes button on the left
    Button *yes_bt = new Button("YES");
    yes_bt->setZValue(2);
    yes_bt->setPos(width()/2 - yes_bt->boundingRect().width()/2 - 40,
                   height()/2 - yes_bt->boundingRect().height()/2);
    connect(yes_bt, SIGNAL(clicked()), this, SLOT(close()) );
    gameScene->addItem(yes_bt);
    gList.append(yes_bt);
    // No button on the right
    Button *no_bt = new Button("NO");
    no_bt->setZValue(2);
    no_bt->setPos(width()/2 - no_bt->boundingRect().width()/2 + 40,
                  height()/2 - no_bt->boundingRect().height()/2);
    connect(no_bt, SIGNAL(clicked()), this, SLOT(notSure()));
    gameScene->addItem(no_bt);
    gList.append(no_bt);
}

// remove the areYouSure window
void Game::notSure()
{
    // assume 3 items are added to gList after click on the quit button
    for (int i = 0; i < 3; i++){
        int index = gList.size();
        gameScene->removeItem(gList[index-1]);
        gList.pop_back();
    }
}

void Game::restart()
{
    qDebug() << "[game] [restart]";
    // clean grid and pieces
    cleanGridPiece();
    // refresh the scene, remove every thing from the scene for now
    cleanWindow();
    // initialize the chessboard, make new board and store them in game->chess_main_board;
    chess_main_board->resetBoard();
    // set current side as 1, red first;
    this->currentSide = 1;
}

void Game::close()
{
    QApplication::quit();
}

