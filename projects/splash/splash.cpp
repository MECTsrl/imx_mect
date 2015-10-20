#include <stdio.h>
#include "splash.h"
#include "ui_splash.h"

splash::splash(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::splash)
{
    ui->setupUi(this);

    QString style;
    if (strlen(picture))
    {
        style.append(QString("image: url(%1);\n").arg(picture));
    }
    if (strlen(bgcolor))
    {
        style.append(QString("background-color: rgb(%1);\n").arg(bgcolor));
    }
    ui->label->setText(text);
    if (strlen(text))
    {
        if (strlen(fontsize) == 0)
        {
            sprintf (fontsize, "%d", 24);
        }
        if (strlen(fontname) == 0)
        {
            sprintf (fontname, "%s", "Ubuntu");
        }
        if (strlen(color))
        {
            style.append(QString("color: rgb(%1);\n").arg(color));
        }
        style.append(QString("font: %1pt \"%2\";").arg(fontsize).arg(fontname));
    }
    ui->label->setStyleSheet(style);
    fprintf (stderr, "%s", style.toAscii().data());
}

splash::~splash()
{
    delete ui;
}

void splash::on_pushButtonQuit_clicked()
{
    exit(0);
}
