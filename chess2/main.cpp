#include "window.h"
#include "start_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //window w;
    //w.resize(480,272);
    //w.show();
    start_window w;
    w.resize(480,272);
    w.show();
    return a.exec();
}
