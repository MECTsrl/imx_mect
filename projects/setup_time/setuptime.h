#ifndef SETUPTIME_H
#define SETUPTIME_H

#include <QWidget>

namespace Ui {
class setupTime;
}

class setupTime : public QWidget
{
    Q_OBJECT
    
public:
    explicit setupTime(QWidget *parent = 0);
    ~setupTime();
    
private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::setupTime *ui;
};

#endif // SETUPTIME_H
