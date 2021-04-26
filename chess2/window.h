#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPainter>
#include <QString>
#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QPen>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QDialog>
#include <QtMath>
#include <QDebug>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class window; }
QT_END_NAMESPACE

class window : public QWidget
{
    Q_OBJECT

public:
    window(QWidget *parent = nullptr);
    ~window();
    void reset();
public slots:
    void mychess_move();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private slots:
    void on_flipButton_clicked();

private:
    QImage image;
    QPen pen;
    //general board
    const int unit = 24;
    const int xstart = 144;
    const int ystart = 18;
    //zoom effect
    const int u_zoom = 45;
    const int x_zoom = 60;
    const int y_zoom = 41;

    //chess
    int chessboard[9][10] = {{0}};
    int moveboard[9][10] = {{0}};
    QString chess_name[20];
    bool side;
    bool selected;
    int board_image;

    QTimer *timer;
    int chosen;
    int chosenx;
    int choseny;
    int destx;
    int desty;
    int curr_x;
    int curr_y;
    int destx_slot;
    int desty_slot;
    Ui::window *ui;

    void infantry();
    void battery();
    void chariot();
    void cavery();
    void elephant();
    void guard();
    void general();
    int win;
};
#endif // WINDOW_H
