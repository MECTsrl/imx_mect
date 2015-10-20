#include "picture.h"
#include "ui_picture.h"

Picture::Picture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Picture)
{
    ui->setupUi(this);
	ui->label->setPixmap(QPixmap("/root/4CTestSuiteBis/picture.png"));
}

Picture::~Picture()
{
    delete ui;
}

void Picture::on_pushButton_clicked()
{
	this->hide();
}
