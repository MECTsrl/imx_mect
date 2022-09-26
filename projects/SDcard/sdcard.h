#ifndef SDCARD_H
#define SDCARD_H

#include <QWidget>
#include <QString>

namespace Ui {
class sdcard;
}

class sdcard : public QWidget
{
    Q_OBJECT
    
public:
    explicit sdcard(bool isExt3, QWidget *parent = 0);
    ~sdcard();
    
private slots:
    void on_pushButtonIgnore_clicked();
    void on_pushButtonApplication_clicked();
    void on_pushButtonStore_clicked();
    void on_pushButtonRemind_clicked();

private:
    void updateSwapSize(QString swapSize);
    Ui::sdcard *ui;
    QString swapSizeFile;
};

#endif // SDCARD_H
