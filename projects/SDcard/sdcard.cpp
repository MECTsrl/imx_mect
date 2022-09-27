#include "sdcard.h"
#include "ui_sdcard.h"
#include <QFile>
#include <QFileInfo>
#include <QWidget>
#include <QDir>
#include <QCoreApplication>


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
            if (swapDir.mkpath(swapPath))  {
                fprintf(stderr, "Created Swap Path: [%s]\n", swapPath.toLatin1().data());
            }
            else  {
                fprintf(stderr, "Error Creating Swap Path: [%s]\n", swapPath.toLatin1().data());
                isExt3 = false;
            }
        }
        else  {
            fprintf(stderr, "Swap Path: [%s] already present\n", swapPath.toLatin1().data());
        }
    }
    // Names of Swap files
    swapSizeFile = QString("%1/.swap_size") .arg(swapPath);
    swapFile = QString("%1/swap_file") .arg(swapPath);
    // Clean Previous files
    cleanUp();
    // Enabling SD Card EXT Swap Params
    ui->chkSwap->setChecked(isExt3);
    ui->chkSwap->setVisible(isExt3);
    ui->comboBox->setVisible(isExt3);
    // Hide Progress Bar and info labels
    ui->prgSwapFile->setVisible(false);
    ui->labelP->setVisible(false);
    ui->labelMB->setVisible(false);
    ui->labelAction->setVisible(false);
    myTimer_ms = 3000;      // 3s Info Refresh
    timerId = 0;
    nSwapSize = 0;
    nStep = -1;
    nExitCode = 0;
    sdCreationProcess = 0;
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
    nExitCode = 2;
    // Add Combobox value if Swap file is selected
    if (ui->chkSwap->isChecked())  {        
        createSwap(ui->comboBox->currentText());
    }
    else  {
        exit(nExitCode);
    }
}

void sdcard::on_pushButtonStore_clicked()
{

    nExitCode = 3;
    // Add Combobox value if Swap file is selected
    if (ui->chkSwap->isChecked())  {
        createSwap(ui->comboBox->currentText());
    }
    else  {
        exit(nExitCode);
    }
}

void sdcard::updateSwapSize(QString swapSize)
// Write requested Swap Size to SD Card
{
    if (! swapSize.isEmpty())  {        
        QString szCommand = QString("echo '%1' > %2") .arg(swapSize) .arg(swapSizeFile);
        system(szCommand.toLatin1().data());
    }
}

void sdcard::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    QCoreApplication::processEvents();

    int nSizeMB = 0;
    if (nStep <= 0)  {
        return;
    }
    else if (nStep == 1)  {
        // Creation of Swap File
        QFileInfo  swapInfo(swapFile);
        if (swapInfo.exists())  {
            nSizeMB = (swapInfo.size() / 1024) / 1024;
            int nProgress = (100 * nSizeMB) / nSwapSize;
            ui->prgSwapFile->setValue(nProgress);
        }
        else {
            fprintf(stderr, "Swap File [%s] not found()!\n", swapFile.toLatin1().data());
        }
    }
    else if (nStep > 1)  {
        // Permissions and Formatting  Swap File
        nSizeMB = nSwapSize;
        ui->prgSwapFile->setValue(100);
    }
    // Refresh values
    ui->labelMB->setText(QString("%1/%2") .arg(nSizeMB, 3, 10) .arg(QString::number(nSwapSize)));
    ui->prgSwapFile->update();
    ui->labelMB->update();
    ui->labelAction->update();
}

void sdcard::createSwap(QString swapSize)
{
    nSwapSize = swapSize.toInt();
    if (nSwapSize > 0)  {
        // Disabling Push Buttons
        ui->pushButtonApplication->setEnabled(false);
        ui->pushButtonIgnore->setEnabled(false);
        ui->pushButtonRemind->setEnabled(false);
        ui->pushButtonStore->setEnabled(false);
        // Hiding SD Card Swap Params
        ui->chkSwap->setVisible(false);
        ui->comboBox->setVisible(false);
        // Hide Progress Bar and info labels
        ui->labelAction->setVisible(true);
        ui->prgSwapFile->setVisible(true);
        ui->labelP->setVisible(true);
        ui->labelMB->setVisible(true);
        // update Swap Size File (immediate Execution)
        fprintf(stderr, "Write Swap Size File:[%s] MB:[%d]\n", swapSizeFile.toLatin1().data(), nSwapSize);
        updateSwapSize(swapSize);
        // Starting Swap file Creation
        nStep = 0;
        ui->labelAction->setText(QString("Creating %1 MB Swap File") .arg(nSwapSize));
        fprintf(stderr, "Creating Swap File:[%s] for MB:[%d]\n", swapFile.toLatin1().data(), nSwapSize);
        // Activate Timer
        nStep = 1;
        timerId = startTimer(myTimer_ms);
        // Starting Shell process
        QString szCommand = QString("dd if=/dev/zero of=%1 bs=1024 count=%2") .arg(swapFile) .arg(nSwapSize * 1024);
        sdCreationProcess = new QProcess(this);
        connect(sdCreationProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(swapCreated(int, QProcess::ExitStatus)));
        connect(sdCreationProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(creationFailed(QProcess::ProcessError)));
        sdCreationProcess->start("sh", QStringList() << "-c" << szCommand);
    }
    else  {
        exit(nExitCode);
    }
}


void sdcard::swapCreated(int exitCode, QProcess::ExitStatus exitStatus)
// Swap Creation ended
{
    if (exitStatus == QProcess::NormalExit && exitCode == 0)  {
        fprintf(stderr, "Swap Created successfully, exit Code: [%d]\n",  exitCode);
        QString szCommand;
        // Setting Swap Permissions
        nStep = 2;
        ui->labelAction->setText("Setting Swap file permissions");
        fprintf(stderr, "Setting Swap file permissions\n");
        szCommand = QString("chmod 0600 %1") .arg(swapFile);
        system(szCommand.toLatin1().data());
        // Formatting Swap file
        nStep = 3;
        ui->labelAction->setText("Formatting Swap file");
        fprintf(stderr, "Formatting Swap file: [%s]\n", swapFile.toLatin1().data());
        szCommand = QString("mkswap %1") .arg(swapFile);
        system(szCommand.toLatin1().data());
        exit(nExitCode);
    }
    else  {
        nStep = -1;
        fprintf(stderr, "Error Creating Swap File, exit Code: [%d]\n",  exitCode);
        cleanUp();
        exit(0);
    }
}

void sdcard::creationFailed(QProcess::ProcessError error)
// Swap Creation Failed
{
    nStep = -1;
    fprintf(stderr, "Error Creating Swap File, exit Code: [%d]\n",  error);
    cleanUp();
    exit(0);
}


void sdcard::cleanUp()
{
    if (QFile::exists(swapSizeFile))  {
        fprintf(stderr, "Removed swap Size file: [%s]\n", swapSizeFile.toLatin1().data());
        QFile::remove(swapSizeFile);
    }
    // Clean Previous Swap File
    if (QFile::exists(swapFile))  {
        fprintf(stderr, "Removed swap file: [%s]\n", swapFile.toLatin1().data());
        QFile::remove(swapFile);
    }
}
