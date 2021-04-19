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


QT_BEGIN_NAMESPACE
namespace Ui { class window; }
QT_END_NAMESPACE

class window : public QWidget
{
    Q_OBJECT

public:
    window(QWidget *parent = nullptr);
    ~window();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QImage image;
    QPen pen;
    //general board
    const int unit = 30;
    const int xstart = 120;
    const int ystart = 1;
    //zoom effect
    const int u_zoom = 45;
    const int x_zoom = 60;
    const int y_zoom = 41;

    //chess
    int chessboard[9][10] = {{0}};
    bool side;
    int board_image;
    Ui::window *ui;
};
#endif // WINDOW_H
