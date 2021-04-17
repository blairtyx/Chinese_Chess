#include "game.h"
#include "button.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QDebug>


Game::Game(QWidget *parent): QGraphicsView(parent)
{
    // create a scene
    gameScene = new QGraphicsScene(this);


    // set size of th scene
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
    bg_brush.setColor(Qt::black);
    setBackgroundBrush(bg_brush);
}

void Game::showWelcomeMenu()
{
    // Show the Game name
    QGraphicsTextItem *nameText = new QGraphicsTextItem("Chinese Chess");
    QFont nameFont("arial", 30);
    nameText->setFont(nameFont);
    nameText->setPos(width()/2 - nameText->boundingRect().width()/2, 30);
    gameScene->addItem(nameText);
    gList.append(nameText);

    // Show the author
    QGraphicsTextItem *auText = new QGraphicsTextItem("L & X");
    QFont auFont("arial", 10);
    auText->setFont(auFont);
    auText->setPos(width()/2 - auText->boundingRect().width()/2, nameText->y() + nameText->boundingRect().height() + 10);
    gameScene->addItem(auText);
    gList.append(auText);

    // Show the play button
    Button *play_bt = new Button("2 Players");
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
    connect(quit_bt, SIGNAL(clicked()), this, SLOT(close()));
    gameScene->addItem(quit_bt);
    gList.append(quit_bt);
}

void Game::start()
{

    qDebug() << "[back in game] start";
}

void Game::guide()
{
    qDebug() << "[back in game] guide";
}
