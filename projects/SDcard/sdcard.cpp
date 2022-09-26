#include "sdcard.h"
#include "ui_sdcard.h"
#include <QFile>


// SD Mount Point

sdcard::sdcard(bool isExt3, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sdcard)
{
    ui->setupUi(this);
    QString   swapPath = QString("/local/sd_card/swap");
    if (isExt3)  {
        // Create Swap Path
        QDir swapDir(swapPath);
        if (! swapDir.exists())  {
            swapDir.mkpath(swapPath);
        }
    }
    // Clean Previous Size file
    swapSizeFile = QString("%1/.swap_size") .arg(swapPath);
    if (QFile::exists(swapSizeFile))  {
        QFile::remove(swapSizeFile);
    }
    // Enabling SD Card EXT Swap Params
    ui->chkSwap->setVisible(isExt3);
    ui->comboBox->setVisible(isExt3);
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
