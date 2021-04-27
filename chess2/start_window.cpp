#include "start_window.h"
#include "ui_start_window.h"

#include <QWidget>
#include "window.h"

start_window::start_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start_window)
{
    ui->setupUi(this);
}

start_window::~start_window()
{
    delete ui;
}

void start_window::on_startButton_clicked()
{
    w.resize(480,272);
    w.show();
}

void start_window::on_endButton_clicked()
{
    close();
}

