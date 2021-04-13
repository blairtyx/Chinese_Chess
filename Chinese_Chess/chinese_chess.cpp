#include "chinese_chess.h"
#include "ui_chinese_chess.h"

chinese_chess::chinese_chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chinese_chess)
{
    ui->setupUi(this);
}

chinese_chess::~chinese_chess()
{
    delete ui;
}

