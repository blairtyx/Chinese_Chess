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
    //image.fill(qRgb(255,255,255));
    setAttribute(Qt::WA_StaticContents);
    side = false;
    selected = false;
    board_image = 0;
    chosen = 0;
    win = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mychess_move()));
    ui->setupUi(this);
    chess_name[1] = "兵";
    chess_name[2] = "炮";
    chess_name[3] = "车";
    chess_name[4] = "马";
    chess_name[5] = "相";
    chess_name[6] = "仕";
    chess_name[7] = "帅";
    chess_name[9] = "卒";
    chess_name[10] = "砲";
    chess_name[11] = "車";
    chess_name[12] = "馬";
    chess_name[13] = "象";
    chess_name[14] = "士";
    chess_name[15] = "将";
    //infantry
    for (int i = 0;i<5;i++) {
        chessboard[2*i][3] = 9;
        chessboard[2*i][6] = 1;
    }
    //battery
    chessboard[1][2] = 10;
    chessboard[7][2] = 10;
    chessboard[1][7] = 2;
    chessboard[7][7] = 2;
    //chariot
    chessboard[0][0] = 11;
    chessboard[8][0] = 11;
    chessboard[0][9] = 3;
    chessboard[8][9] = 3;
    //cavery
    chessboard[1][0] = 12;
    chessboard[7][0] = 12;
    chessboard[1][9] = 4;
    chessboard[7][9] = 4;
    //elephant
    chessboard[2][0] = 13;
    chessboard[6][0] = 13;
    chessboard[2][9] = 5;
    chessboard[6][9] = 5;
    //guard
    chessboard[3][0] = 14;
    chessboard[5][0] = 14;
    chessboard[3][9] = 6;
    chessboard[5][9] = 6;
    //general
    chessboard[4][0] = 15;
    chessboard[4][9] = 7;
}

window::~window()
{
    delete ui;
}


void window::mousePressEvent(QMouseEvent *event) {
    if (win) {
        reset();
        close();
    }
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
            if(chessboard[x][y]>0&&((bool)(chessboard[x][y]-8>0))==side){
                for(int i = 0;i<9;i++) {
                    for (int j = 0;j<10;j++) {
                        moveboard[i][j] = 0;
                    }
                }
                chosen = chessboard[x][y];
                curr_x = xstart+x*unit;
                curr_y = ystart +y*unit;
                chosenx = x;
                choseny = y;
                int type;
                if(chessboard[x][y]>8) {
                    type = chessboard[x][y]-8;
                } else {
                    type = chessboard[x][y];
                }
                if (type == 1) {
                    infantry();
                } else if (type == 2) {
                    battery();
                }
                else if (type == 3) {
                    chariot();
                } else if (type == 4) {
                    cavery();
                } else if (type == 5) {
                    elephant();
                } else if (type == 6) {
                    guard();
                } else if (type == 7) {
                    general();
                } else {
                    return;
                }
            } else if (chosen>0) {
                if (moveboard[x][y] == 1) {
                    destx_slot = x;
                    desty_slot = y;
                    destx = xstart+x*unit;
                    desty = ystart +y*unit;
                    chessboard[chosenx][choseny] = 0;
                    board_image = 0;
                    timer->start(20);
                    selected = true;
                    for(int i = 0;i<9;i++) {
                        for (int j = 0;j<10;j++) {
                            moveboard[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    update();
    return;
}

void window::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rec = event->rect();
    //painter.drawImage(rec,image,rec);
    if (board_image == 0) {
        painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
        for (int i = 0;i<9;i++) {
            for (int j = 0;j<10;j++) {
                if (moveboard[i][j] == 1) {
                    painter.drawRect(xstart+i*unit-unit/2,ystart+j*unit-unit/2,unit,unit);
                }
            }
        }
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
                if (chessboard[i][j] >0) {
                    if (chessboard[i][j] <8) {
                        painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                        painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                    } else {
                        painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                        painter.setPen(QPen(Qt::white,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                    }
                    painter.drawEllipse(xstart+i*unit-unit/2,ystart+j*unit-unit/2,unit,unit);
                    painter.drawText(xstart+i*unit-6,ystart+j*unit+6,chess_name[chessboard[i][j]]);
                }
            }
        }
        if (selected) {
            if (chosen <8) {
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            } else {
                painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                painter.setPen(QPen(Qt::white,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            }
            painter.drawEllipse(curr_x-unit/2,curr_y-unit/2,unit,unit);
            painter.drawText(curr_x-6,curr_y+6,"棋");
        }
    } else if(board_image == 2) {
        painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
        for (int i = 0;i<9;i++) {
            for (int j = 0;j<5;j++) {
                if (moveboard[i][j+5] == 1) {
                    painter.drawRect(x_zoom+i*u_zoom-u_zoom/2,y_zoom+j*u_zoom-u_zoom/2,u_zoom,u_zoom);
                }
            }
        }
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
        for (int i = 0;i<9;i++) {
            for (int j = 0;j<5;j++) {
                if (chessboard[i][j+5] >0) {
                    if (chessboard[i][j+5]<8) {
                        painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                        painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                    } else {
                        painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                        painter.setPen(QPen(Qt::white,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                    }
                    painter.drawEllipse(x_zoom+i*u_zoom-u_zoom/2,y_zoom+j*u_zoom-u_zoom/2,u_zoom,u_zoom);
                    painter.drawText(x_zoom+i*u_zoom-6,y_zoom+j*u_zoom+6,chess_name[chessboard[i][j+5]]);
                }
            }
        }
    } else {
        painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
        for (int i = 0;i<9;i++) {
            for (int j = 0;j<5;j++) {
                if (moveboard[i][j] == 1) {
                    painter.drawRect(x_zoom+i*u_zoom-u_zoom/2,y_zoom+j*u_zoom-u_zoom/2,u_zoom,u_zoom);
                }
            }
        }
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
                if (chessboard[i][j] >0) {
                    if (chessboard[i][j] <8) {
                        painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                        painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                    } else {
                        painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                        painter.setPen(QPen(Qt::white,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                    }
                    painter.drawEllipse(x_zoom+i*u_zoom-u_zoom/2,y_zoom+j*u_zoom-u_zoom/2,u_zoom,u_zoom);
                    painter.drawText(x_zoom+i*u_zoom-6,y_zoom+j*u_zoom+6,chess_name[chessboard[i][j]]);
                }
            }
        }
    }
    if (win) {
        selected = true;
        painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
        painter.drawRect(0,0,480,272);
        if (side) {
            painter.setPen(QPen(Qt::red,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.drawText(215,130,"red wins!");
        } else {
            painter.setPen(QPen(Qt::blue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.drawText(215,130,"blue wins!");
        }
    }

}

void window::mychess_move() {
    if ((desty-curr_y)*(desty-curr_y)+(destx-curr_x)*(destx-curr_x) < 225) {
        if (chessboard[destx_slot][desty_slot] == 7||chessboard[destx_slot][desty_slot] == 15) {
            win = 1;
        }
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

void window::infantry() {
    int x = chosenx;
    int y = choseny;
    moveboard[x][y]=1;
    if (!side) {
        // if haven't pass the river
        if (y < 5 && y >=0){
            if (x > 0 && x < 8){
                moveboard[x-1][y]=1;
                moveboard[x+1][y]=1;
            } else if (x == 0){
                moveboard[x+1][y]=1;
            } else if (x == 8) {
                moveboard[x-1][y]=1;
            }
        }
        if (y > 0) {
            moveboard[x][y-1]=1;
        }

    }
    // for blue side
    else {
        // if haven't pass the river
        if (y < 9) {
            moveboard[x][y+1]=1;
        }
        if (y > 4 && y <= 9) {
            if (x > 0 && x<8){
                moveboard[x-1][y]=1;
                moveboard[x+1][y]=1;
            } else if (x == 0) {
                moveboard[x+1][y]=1;
            } else if (x == 8) {
                moveboard[x-1][y]=1;
            }
        }
    }
}

void window::battery() {
    int x = chosenx;
    int y = choseny;
    int x_other = x-1;
    int y_other = y-1;
    //highlight this grid
    moveboard[x][y]=1;
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    // for red side
    while (x_other>=0&& (chessboard[x_other][y]==0)) {
        moveboard[x_other--][y]= 1;
    }
    x_other--;
    while (x_other>=0) {
        if (chessboard[x_other][y]>0) {
            moveboard[x_other][y]=1;
            break;
        }
        x_other--;
    }

    x_other = x+1;
    while (x_other<9 && (chessboard[x_other][y]==0)) {
        moveboard[x_other++][y] = 1;
    }
    x_other++;
    while (x_other<9) {
        if (chessboard[x_other][y]>0) {
            moveboard[x_other][y]= 1;
            break;
        }
        x_other++;
    }

    while (y_other>=0 && (chessboard[x][y_other]==0)) {
        moveboard[x][y_other--]=1;
    }
    y_other--;
    while (y_other>=0) {
        if (chessboard[x][y_other]>0) {
            moveboard[x][y_other]=1;
            break;
        }
        y_other--;
    }

    y_other = y+1;

    while (y_other<10 && (chessboard[x][y_other]==0)) {
        moveboard[x][y_other++]=1;
    }
    y_other++;
    while (y_other<10) {
        if (chessboard[x][y_other]>0) {
            moveboard[x][y_other]=1;
            break;
        }
        y_other++;
    }
}

void window::chariot() {
    int x = chosenx;
    int y = choseny;
    int x_other = x-1;
    int y_other = y-1;
    //highlight this grid
    moveboard[x][y]=1;
    // highlight target grid
    // add these highlighted grid to game->highlightedGrid
    // for red side

    while (x_other>=0&& (chessboard[x_other][y]==0)) {
        moveboard[x_other--][y]= 1;
    }
    if (x_other>=0&&chessboard[x_other][y]>0) {
        moveboard[x_other][y] = 1;
    }

    x_other = x+1;
    while (x_other<9 && (chessboard[x_other][y]==0)) {
        moveboard[x_other++][y] = 1;
    }
    if (x_other<9 &&chessboard[x_other][y]>0) {
        moveboard[x_other][y] = 1;
    }

    while (y_other>=0 && (chessboard[x][y_other]==0)) {
        moveboard[x][y_other--]=1;
    }

    if (y_other>=0&&chessboard[x][y_other]>0) {
        moveboard[x][y_other] = 1;
    }

    y_other = y+1;

    while (y_other<10 && (chessboard[x][y_other]==0)) {
        moveboard[x][y_other++]=1;
    }

    if (y_other<10&&chessboard[x][y_other]>0) {
        moveboard[x][y_other] = 1;
    }
}

void window::cavery() {
    int x = chosenx;
    int y = choseny;
    if (x>1&&chessboard[x-1][y] == 0) {
        if (y>0) {
            moveboard[x-2][y-1]=1;
        }
        if (y<9) {
            moveboard[x-2][y+1]= 1;
        }
    }

    if (x<7&&chessboard[x+1][y]==0) {
        if (y>0) {
            moveboard[x+2][y-1]=1;
        }
        if (y<9) {
            moveboard[x+2][y+1]=1;
        }
    }

    if (y>1&&chessboard[x][y-1]==0) {
        if (x>0) {
            moveboard[x-1][y-2]=1;
        }
        if (x<8) {
            moveboard[x+1][y-2]=1;
        }
    }

    if (y<8&&chessboard[x][y+1]==0) {
        if (x>0) {
            moveboard[x-1][y+2]=1;
        }
        if (x<8) {
            moveboard[x+1][y+2]=1;
        }
    }
}

void window::elephant() {
    int x = chosenx;
    int y = choseny;
    if (side) {
        if (x>1&&y>1&&chessboard[x-1][y-1]== 0) {
            moveboard[x-2][y-2] = 1;
        }
        if (x>1&&y<3&&chessboard[x-1][y+1]==0) {
            moveboard[x-2][y+2] = 1;
        }
        if (x<7&&y<3&&chessboard[x+1][y+1]==0) {
            moveboard[x+2][y+2] = 1;
        }
        if (x<7&&y>1&&chessboard[x+1][y-1]==0) {
            moveboard[x+2][y-2] = 1;
        }

    }
    // for red side
    else {
        if (x>1&&y>6&&chessboard[x-1][y-1]==0) {
            moveboard[x-2][y-2]=1;
        }
        if (x>1&&y<8&&chessboard[x-1][y+1]==0) {
            moveboard[x-2][y+2]=1;
        }
        if (x<7&&y<8&&chessboard[x+1][y+1]==0) {
            moveboard[x+2][y+2]=1;
        }
        if (x<7&&y>6&&chessboard[x+1][y-1]==0) {
            moveboard[x+2][y-2]=1;
        }

    }
}

void window::guard() {
    int x = chosenx;
    int y = choseny;
    if (side) {
        if (x>3&&y>0) {
            moveboard[x-1][y-1]=1;
        }
        if (x>3&&y<2) {
            moveboard[x-1][y+1]=1;
        }
        if (x<5&&y<2) {
            moveboard[x+1][y+1]=1;
        }
        if (x<5&&y>0) {
            moveboard[x+1][y-1]=1;
        }

    }
    // for red side
    else {
        if (x>3&&y>7) {
            moveboard[x-1][y-1]=1;
        }
        if (x>3&&y<9) {
            moveboard[x-1][y+1]=1;
        }
        if (x<5&&y<9) {
            moveboard[x+1][y+1]=1;
        }
        if (x<5&&y>7) {
            moveboard[x+1][y-1]=1;
        }
    }
}

void window::general() {
    int x = chosenx;
    int y = choseny;
    if (x>3) {
        moveboard[x-1][y]=1;
    }
    if (x<5) {
        moveboard[x+1][y]=1;
    }
    // for blue side
    if (side) {
        if (y>0) {
            moveboard[x][y-1]=1;
        }
        if (y<2) {
            moveboard[x][y+1]=1;
        }

    }
    // for red side
    else {
        if (y>7) {
            moveboard[x][y-1]=1;
        }
        if (y<9) {
            moveboard[x][y+1]=1;
        }

    }
}

void window::on_flipButton_clicked()
{
    win = 1;
    update();
}

void window::reset() {
    for (int i = 0;i<9;i++) {
        for (int j = 0;j<10;j++) {
            chessboard[i][j] = 0;
            moveboard[i][j] = 0;
        }
    }
    side = false;
    selected = false;
    board_image = 0;
    chosen = 0;
    win = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mychess_move()));
    chess_name[1] = "兵";
    chess_name[2] = "炮";
    chess_name[3] = "车";
    chess_name[4] = "马";
    chess_name[5] = "相";
    chess_name[6] = "仕";
    chess_name[7] = "帅";
    chess_name[9] = "卒";
    chess_name[10] = "砲";
    chess_name[11] = "車";
    chess_name[12] = "馬";
    chess_name[13] = "象";
    chess_name[14] = "士";
    chess_name[15] = "将";
    //infantry
    for (int i = 0;i<5;i++) {
        chessboard[2*i][3] = 9;
        chessboard[2*i][6] = 1;
    }
    //battery
    chessboard[1][2] = 10;
    chessboard[7][2] = 10;
    chessboard[1][7] = 2;
    chessboard[7][7] = 2;
    //chariot
    chessboard[0][0] = 11;
    chessboard[8][0] = 11;
    chessboard[0][9] = 3;
    chessboard[8][9] = 3;
    //cavery
    chessboard[1][0] = 12;
    chessboard[7][0] = 12;
    chessboard[1][9] = 4;
    chessboard[7][9] = 4;
    //elephant
    chessboard[2][0] = 13;
    chessboard[6][0] = 13;
    chessboard[2][9] = 5;
    chessboard[6][9] = 5;
    //guard
    chessboard[3][0] = 14;
    chessboard[5][0] = 14;
    chessboard[3][9] = 6;
    chessboard[5][9] = 6;
    //general
    chessboard[4][0] = 15;
    chessboard[4][9] = 7;
    update();
}
