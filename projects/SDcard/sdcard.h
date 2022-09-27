#ifndef SDCARD_H
#define SDCARD_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QTimerEvent>
#include <QProcess>
#include <QStringList>

namespace Ui {
class sdcard;
}

class sdcard : public QWidget
{
    Q_OBJECT
    
public:
    explicit sdcard(bool isExt3, QWidget *parent = 0);
    ~sdcard();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void on_pushButtonIgnore_clicked();
    void on_pushButtonApplication_clicked();
    void on_pushButtonStore_clicked();
    void on_pushButtonRemind_clicked();
    void swapCreated(int exitCode, QProcess::ExitStatus exitStatus);
    void creationFailed(QProcess::ProcessError error);

private:
    void createSwap(QString swapSize);
    void updateSwapSize(QString swapSize);
    void cleanUp();

    Ui::sdcard              *ui;
    QString                 swapSizeFile;       // File to hold swap Size
    QString                 swapFile;           // Swap file name
    int                     nSwapSize;          // Size of required Swap File in MB
    int                     timerId;            // Module Timer ID
    int                     myTimer_ms;         // Module Timer Interval
    int                     nStep;              // Work Step
    int                     nExitCode;          // Exit Code if swap creation enabled
    QProcess                *sdCreationProcess; // Command in execution
};

#endif // SDCARD_H
