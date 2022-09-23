#include "sdcard.h"
#include "ui_sdcard.h"
#include <QFile>

// SD Mount Point

sdcard::sdcard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sdcard)
{
    ui->setupUi(this);
    swapSizeFile = QString("/local/sd_card/.swap_size");
    // Clean Previous Size file
    if (QFile::exists(swapSizeFile))  {
        QFile::remove(swapSizeFile);
    }
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

    // Add Combobox value if Swap file is selected
    if (ui->chkSwap->isChecked())  {        
        updateSwapSize(ui->comboBox->currentText());
    }
    exit(2);
}

void sdcard::on_pushButtonStore_clicked()
{

    // Add Combobox value if Swap file is selected
    if (ui->chkSwap->isChecked())  {
        updateSwapSize(ui->comboBox->currentText());
    }
    exit(3);
}

void sdcard::updateSwapSize(QString swapSize)
// Write requested Swap Size to SD Card
{
    if (! swapSize.isEmpty())  {
        QString szCommand = QString("echo '%1' > %2") .arg(swapSize) .arg(swapSizeFile);
        system(szCommand.toLatin1().data());
    }
}
