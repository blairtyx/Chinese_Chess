#include "chinese_chess.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chinese_chess w;
    w.show();
    return a.exec();
}
