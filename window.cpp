#include "window.h"
#include "ui_window.h"

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QPen>
#include <QBrush>

window::window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::window)
{
    image.fill(qRgb(255,255,255));
    setAttribute(Qt::WA_StaticContents);
    side = false;
    board_image = 0;
    ui->setupUi(this);
}

window::~window()
{
    delete ui;
}


void window::mousePressEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    if (board_image == 0) {
        if (y<131) {
            board_image = 1;
        } else {
            board_image = 2;
        }
    } else {
        if (x<x_zoom-u_zoom/2||x>480-x_zoom+u_zoom/2) {
            board_image = 0;
        } else if (y<y_zoom-u_zoom/2||y>272-y_zoom+u_zoom/2){
            return;
        } else {
            x = (x-x_zoom+u_zoom/2)/u_zoom;
            y = (y-y_zoom+u_zoom/2)/u_zoom;
            if (board_image == 2) {
                y = y+5;
            }
            chessboard[x][y] = 1;
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
                }
            }
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
                    painter.drawEllipse(x_zoom+i*u_zoom-unit/2,y_zoom+j*u_zoom-unit/2,unit,unit);
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
                    painter.drawEllipse(x_zoom+i*u_zoom-unit/2,y_zoom+j*u_zoom-unit/2,unit,unit);
                }
            }
        }
    }

    if (side) {
        painter.drawLine(300,300,500,500);
    }
}



