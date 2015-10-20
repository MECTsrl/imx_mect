#include "Qt4CTestSuiteBis.h"
#include "ui_Qt4CTestSuiteBis.h"
#include <QMessageBox>
#include <string.h>

#define TRUE_STRING "true"
#define FALSE_STRING "false"
#define ERROR_STRING "ERROR"

Qt4CTestSuiteBis::Qt4CTestSuiteBis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Qt4CTestSuiteBis)
{
    ui->setupUi(this);
    if (comm.connect(REMOTE_ADDRESS, REMOTE_PORT) == false)
    {
        QMessageBox::critical(0, "ERROR",QString("CANNOT OPEN %1 %2").arg(REMOTE_ADDRESS).arg(REMOTE_PORT));
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh4C()));
    timer->start(HMI_PERIOD_MS);
	picturew = NULL;
}

bool Qt4CTestSuiteBis::refresh4C()
{
    char value[32];
    if (readvar("tot_counter", value) == false)
	{
		strcpy(value, ERROR_STRING);
	}
    ui->lineEdit1->setText(value);
    if (readvar("tot_positive", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
    ui->lineEdit2->setText(value);
    if (readvar("tot_negative", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
    ui->lineEdit3->setText(value);
    if (readvar("enable_pos_log", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
	ui->groupBox4->setTitle(QString("enable_pos_log: %1").arg(value));
    if (readvar("disable_pos_log", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
	ui->groupBox5->setTitle(QString("disable_pos_log: %1").arg(value));
    if (readvar("enable_library", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
	ui->groupBox7->setTitle(QString("enable_library: %1").arg(value));
    if (readvar("disable_library", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
	ui->groupBox8->setTitle(QString("disable_library: %1").arg(value));
    if (readvar("counter", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
	ui->lineEdit6->setText(value);
    if (readvar("n", value) == false)
    {
		strcpy(value, ERROR_STRING);
    }
	ui->lineEdit9->setText(value);
    return true;
}

bool Qt4CTestSuiteBis::readvar(const char * name, char * value)
{
    bool ret;
    char myname[32];
    strcpy(myname,name);

    if (comm.readValue(myname, value))
    {
        ret = true;
    }
    else
    {
        strcpy(value, "ERR");
        ret = false;
    }
    //printf("@@@@@@@@ %s = '%s'\n", name, value);
    return ret;
}

bool Qt4CTestSuiteBis::writevar(const char * name, char * value)
{
    bool ret;
    char myname[32];
    strcpy(myname,name);

    if (comm.writeValue(myname, value))
    {
        ret = true;
    }
    else
    {
        strcpy(value, "ERR");
        ret = false;
    }
    //printf("@@@@@@@@ %s = '%s'\n", name, value);
    return ret;
}

Qt4CTestSuiteBis::~Qt4CTestSuiteBis()
{
    comm.disconnect();
    delete ui;
}

void Qt4CTestSuiteBis::on_pushButtonApply4_toggled(bool checked)
{
    char value[3];
    strcpy(value, ((checked == true)?"1":"0"));
    if (writevar("enable_pos_log", value) == false)
    {
        printf("@@@@@@@@ CANNOT WTRITE '%s' = '%s'\n", "enable_pos_log", value);
    }
}

void Qt4CTestSuiteBis::on_pushButtonApply5_toggled(bool checked)
{
    char value[3];
    strcpy(value, ((checked == true)?"1":"0"));
    if (writevar("disable_pos_log", value) == false)
    {
        printf("@@@@@@@@ CANNOT WTRITE '%s' = '%s'\n", "disable_pos_log", value);
    }
}

void Qt4CTestSuiteBis::on_pushButtonApply7_toggled(bool checked)
{
    char value[3];
    strcpy(value, ((checked == true)?"1":"0"));
    if (writevar("enable_library", value) == false)
    {
        printf("@@@@@@@@ CANNOT WTRITE '%s' = '%s'\n", "enable_library", value);
    }
}

void Qt4CTestSuiteBis::on_pushButtonApply8_toggled(bool checked)
{
    char value[3];
    strcpy(value, ((checked == true)?"1":"0"));
    if (writevar("disable_library", value) == false)
    {
        printf("@@@@@@@@ CANNOT WTRITE '%s' = '%s'\n", "disable_library", value);
    }
}

void Qt4CTestSuiteBis::on_pushButtonNext_clicked()
{
    if (picturew == NULL)
	{
		picturew = new Picture();
	}
    picturew->showFullScreen();
}
