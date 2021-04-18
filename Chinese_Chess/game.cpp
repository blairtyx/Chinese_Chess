#include "game.h"
#include "button.h"
#include "cc_board.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QDebug>


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

void Game::drawCCBoard()
{
    chess_main_board = new CC_board();

}

// can close the application with 'ESC' key
void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape){
        close();
    }
}

void Game::areYouSure()
{
    // pop a window
    QGraphicsRectItem *areYouSure = new QGraphicsRectItem();
    areYouSure->setRect(0,0, 150, 100);
    areYouSure->setZValue(2);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
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

void Game::start()
{

    qDebug() << "[back in game] start";

    // refresh the scene
    for (int i = 0, N = gList.size(); i < N ; ++i) {
        gameScene->removeItem(gList[i]);
    }

    // show the chessboard
    drawCCBoard();


}

void Game::guide()
{
    qDebug() << "[back in game] guide";
}

void Game::notSure()
{
    for (int i = 0; i < 3; i++){
        int index = gList.size();
        gameScene->removeItem(gList[index-1]);
        gList.pop_back();
    }


}
