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

void sdcard::on_pushButtonRemind_clicked()
{
    exit(0);
}

void sdcard::on_pushButtonIgnore_clicked()
{
    exit(1);
}

void sdcard::on_pushButtonApplication_clicked()
{
    int nRes = 2;

    // Add Combobox value if Swap file is selected
    if (ui->chkSwap->isChecked())  {
        nRes += ui->comboBox->currentText().toInt();
    }
    exit(nRes);
}

void sdcard::on_pushButtonStore_clicked()
{
    int nRes = 3;

    // Add Combobox value if Swap file is selected
    if (ui->chkSwap->isChecked())  {
        nRes += ui->comboBox->currentText().toInt();
    }
    exit(nRes);
}
