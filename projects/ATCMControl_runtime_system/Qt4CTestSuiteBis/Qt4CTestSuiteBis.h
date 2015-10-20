#ifndef QT4CTESTSUITEBIS_H
#define QT4CTESTSUITEBIS_H

#include <QWidget>
#include "fc_comunication.h"
#include "picture.h"
#include <QTimer>

#define HMI_PERIOD_MS 500
#define HOLD_SAMPLE 5
#define REMOTE_ADDRESS "127.0.0.1"
#define REMOTE_PORT 17290

namespace Ui {
    class Qt4CTestSuiteBis;
}

class Qt4CTestSuiteBis : public QWidget
{
    Q_OBJECT

public:
    explicit Qt4CTestSuiteBis(QWidget *parent = 0);
    ~Qt4CTestSuiteBis();

private slots:
    void on_pushButtonApply4_toggled(bool checked);
    void on_pushButtonApply5_toggled(bool checked);
    void on_pushButtonApply7_toggled(bool checked);
    void on_pushButtonApply8_toggled(bool checked);
    void on_pushButtonNext_clicked();

    bool refresh4C();
private:
    bool readvar(const char * name, char * value);
    bool writevar(const char * name, char * value);

    FC_comunication comm;
    Ui::Qt4CTestSuiteBis *ui;
    QTimer * timer;
    Picture * picturew;
};

#endif // Qt4CTestSuiteBis_H
