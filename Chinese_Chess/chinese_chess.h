#ifndef CHINESE_CHESS_H
#define CHINESE_CHESS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class chinese_chess; }
QT_END_NAMESPACE

class chinese_chess : public QMainWindow
{
    Q_OBJECT

public:
    chinese_chess(QWidget *parent = nullptr);
    ~chinese_chess();

private:
    Ui::chinese_chess *ui;
};
#endif // CHINESE_CHESS_H
