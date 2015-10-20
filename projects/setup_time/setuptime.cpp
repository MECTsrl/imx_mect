#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "setuptime.h"
#include "ui_setuptime.h"

setupTime::setupTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setupTime)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    time_t rt = 0;
    struct tm *pt = NULL;
    ui->retranslateUi(this);

    /* Load data and time 1*/
    rt = time(NULL);
    pt = localtime(&rt);
    if (pt == NULL) {
        fputs(__func__, stderr);
        perror(": while getting local time");
        fflush(stderr);

        return;
    }


    ui->spinBoxAnno->setValue(pt->tm_year + 1900);
    ui->spinBoxMese->setValue(pt->tm_mon + 1);
    ui->spinBoxGiorno->setValue(pt->tm_mday);
    ui->spinBoxOre->setValue(pt->tm_hour);
    ui->spinBoxMinuti->setValue(pt->tm_min);
    showFullScreen();
}

setupTime::~setupTime()
{
    delete ui;
}

void setupTime::on_pushButtonOk_clicked()
{
    /* UPDATE THE SYSTEM CLOCK */
    time_t rt = 0;
    struct tm *pt = NULL;
    struct timezone timez;
    struct timeval temp;
    int rc = 0;

    rt = time(NULL);
    pt = localtime(&rt);
    if (pt == NULL) {
        fputs(__func__, stderr);
        perror(": while getting local time");
        fflush(stderr);

        return;
    }

    pt->tm_year = ui->spinBoxAnno->value() - 1900;
    pt->tm_mon = ui->spinBoxMese->value() - 1;
    pt->tm_mday = ui->spinBoxGiorno->value();

    pt->tm_hour = ui->spinBoxOre->value();
    pt->tm_min = ui->spinBoxMinuti->value();
    pt->tm_sec = 0;

    rc = gettimeofday(&temp, &timez);
    if (rc < 0) {
        fputs(__func__, stderr);
        perror(": while getting time of day");
        fflush(stderr);

        return;
    }

    temp.tv_sec = mktime(pt);
    temp.tv_usec = 0;

    rc = settimeofday(&temp, &timez);
    if (rc < 0) {
        fputs(__func__, stderr);
        perror(": while setting time of day");
        fflush(stderr);

        return;
    }

    system("/sbin/hwclock -wu");        /* Update RTC from system */

    exit(0);
}
