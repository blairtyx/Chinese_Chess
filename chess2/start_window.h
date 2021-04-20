#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <QWidget>
#include "window.h"
namespace Ui {
class start_window;
}

class start_window : public QWidget
{
    Q_OBJECT

public:
    explicit start_window(QWidget *parent = nullptr);
    ~start_window();

private slots:
    void on_startButton_clicked();

private:
    Ui::start_window *ui;
    class window w;
};

#endif // START_WINDOW_H
