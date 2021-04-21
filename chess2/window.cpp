#include "window.h"
#include "ui_window.h"

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QDialog>

window::window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::window)
{
    image.fill(qRgb(255,255,255));
    setAttribute(Qt::WA_StaticContents);
    side = false;
    selected = false;
    board_image = 0;
    chosen = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mychess_move()));
    ui->setupUi(this);

    chessboard[0][0] = 1;
}

window::~window()
{
    delete ui;
}


void window::mousePressEvent(QMouseEvent *event) {
    if (selected) {
        return;
    }
    int x = event->x();
    int y = event->y();
    if (board_image == 0) {
        if (y<131) {
            board_image = 1;
        } else {
            board_image = 2;
        }
    } else {
        if (x<x_zoom-unit/2||x>480-x_zoom+unit/2) {
            board_image = 0;
        } else if (y<y_zoom-unit/2||y>272-y_zoom+unit/2){
            return;
        } else {
            x = (x-x_zoom+u_zoom/2)/u_zoom;
            y = (y-y_zoom+u_zoom/2)/u_zoom;
            if (board_image == 2) {
                y = y+5;
            }
            if (chosen>0) {
                if (chessboard[x][y] == 0) {
                    destx_slot = x;
                    desty_slot = y;
                    destx = xstart+x*unit;
                    desty = ystart +y*unit;
                    chessboard[chosenx][choseny] = 0;
                    board_image = 0;
                    timer->start(20);
                    selected = true;
                }
            } else if(chessboard[x][y] > 0 ){
                    chosen = chessboard[x][y];
                    curr_x = xstart+x*unit;
                    curr_y = ystart +y*unit;
                    chosenx = x;
                    choseny = y;
            }
        }
    }
    update();
    return;
}

void window::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rec = event->rect();
    painter.drawImage(rec,image,rec);
    if (board_image == 0) {
        //draw board
        painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        painter.drawLine(xstart,ystart,xstart,ystart+9*unit);
        painter.drawLine(xstart+8*unit,ystart,xstart+8*unit,ystart+9*unit);
        for (int i = 0;i<9;i++) {
            painter.drawLine(xstart+i*unit,ystart,xstart+i*unit,ystart+4*unit);
            painter.drawLine(xstart+i*unit,ystart+5*unit,xstart+i*unit,ystart+9*unit);

        }
        for (int i = 0;i<10;i++) {
            painter.drawLine(xstart,ystart+i*unit,xstart+8*unit,ystart+i*unit);
        }
        //drawchess
        painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        for (int i = 0;i<9;i++) {
            for (int j = 0;j<10;j++) {
                if (chessboard[i][j] == 1) {
                    painter.drawEllipse(xstart+i*unit-unit/2,ystart+j*unit-unit/2,unit,unit);
                    painter.drawText(xstart+i*unit-6,ystart+j*unit+6,"棋");
                }
            }
        }
        if (selected) {
            painter.drawEllipse(curr_x-unit/2,curr_y-unit/2,unit,unit);
            painter.drawText(curr_x-6,curr_y+6,"棋");
        }
    } else if(board_image == 2) {
        //draw board
        painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        painter.drawLine(x_zoom,0,x_zoom,y_zoom+4*u_zoom);
        painter.drawLine(x_zoom+8*u_zoom,0,x_zoom+8*u_zoom,y_zoom+4*u_zoom);
        for (int i = 0;i<9;i++) {
            painter.drawLine(x_zoom+i*u_zoom,y_zoom,x_zoom+i*u_zoom,y_zoom+4*u_zoom);
        }
        for (int i = 0;i<5;i++) {
            painter.drawLine(x_zoom,y_zoom+i*u_zoom,x_zoom+8*u_zoom,y_zoom+i*u_zoom);
        }
        //draw chess
        painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        for (int i = 0;i<9;i++) {
            for (int j = 0;j<5;j++) {
                if (chessboard[i][j+5] == 1) {
                    painter.drawEllipse(x_zoom+i*u_zoom-u_zoom/2,y_zoom+j*u_zoom-u_zoom/2,u_zoom,u_zoom);
                    painter.drawText(x_zoom+i*u_zoom-6,y_zoom+j*u_zoom+6,"棋");
                }
            }
        }
    } else {
        //draw board
        painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        painter.drawLine(x_zoom,y_zoom,x_zoom,272);
        painter.drawLine(x_zoom+8*u_zoom,y_zoom,x_zoom+8*u_zoom,272);
        for (int i = 0;i<9;i++) {
            painter.drawLine(x_zoom+i*u_zoom,y_zoom,x_zoom+i*u_zoom,y_zoom+4*u_zoom);
        }
        for (int i = 0;i<5;i++) {
            painter.drawLine(x_zoom,y_zoom+i*u_zoom,x_zoom+8*u_zoom,y_zoom+i*u_zoom);
        }
        //draw chess
        painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        for (int i = 0;i<9;i++) {
            for (int j = 0;j<5;j++) {
                if (chessboard[i][j] == 1) {
                    painter.drawEllipse(x_zoom+i*u_zoom-u_zoom/2,y_zoom+j*u_zoom-u_zoom/2,u_zoom,u_zoom);
                    painter.drawText(x_zoom+i*u_zoom-6,y_zoom+j*u_zoom+6,"棋");
                }
            }
        }
    }

}

void window::mychess_move() {
    if ((desty-curr_y)*(desty-curr_y)+(destx-curr_x)*(destx-curr_x) < 225) {
        chessboard[destx_slot][desty_slot] = chosen;
        chosen = 0;
        selected = false;
        side = !side;
        timer->stop();
    } else {
        int a = qSqrt((desty-curr_y)*(desty-curr_y)+(destx-curr_x)*(destx-curr_x));
        curr_x += 20*(destx-curr_x)/a;
        curr_y += 20*(desty-curr_y)/a;
        timer->start(20);
    }
    update();
    return;
}

