#ifndef SDCARD_H
#define SDCARD_H

#include <QWidget>

namespace Ui {
class sdcard;
}

class sdcard : public QWidget
{
    Q_OBJECT
    
public:
    explicit sdcard(QWidget *parent = 0);
    ~sdcard();
    
private slots:
    void on_pushButtonIgnore_clicked();

    void on_pushButtonApplication_clicked();

    void on_pushButtonStore_clicked();

    void on_pushButtonRemind_clicked();

private:
    Ui::sdcard *ui;
};

#endif // SDCARD_H
