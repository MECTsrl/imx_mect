#include "sdcard.h"
#include "ui_sdcard.h"

sdcard::sdcard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sdcard)
{
    ui->setupUi(this);
}

sdcard::~sdcard()
{
    delete ui;
}

void sdcard::on_pushButtonIgnore_clicked()
{
    exit(0);
}

void sdcard::on_pushButtonApplication_clicked()
{
    exit(1);
}

void sdcard::on_pushButtonStore_clicked()
{
    exit(2);
}
