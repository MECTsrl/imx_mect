#include "mac_sn.h"
#include "ui_mac_sn.h"
#include "numpad.h"
#include <stdio.h>
#include <QDate>
#include <QMessageBox>

/**
 * @brief transform a string in hex format into int
 */
static int atoh(const char * string)
{
    int value = 0;
    sscanf (string, "%x", &value);
    return value;
}

mac_sn::mac_sn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mac_sn)
{
    ui->setupUi(this);

    FILE * fp;

    ui->pushButtonSN_1->setText(QDate::currentDate().toString("yyyy"));
    ui->pushButtonSN_2->setText(QDate::currentDate().toString("MM"));
    ui->pushButtonSN_3->setText("");

    fp = fopen(SERIAL_NUMBER_FILE, "r");
    if (fp != NULL)
    {
        char line[32];
        if (fgets(line, 32, fp) != NULL)
        {
            ui->pushButtonSN_1->setText(QString(line).trimmed().mid(0,4));
            ui->pushButtonSN_2->setText(QString(line).trimmed().mid(4,2));
            ui->pushButtonSN_3->setText(QString(line).trimmed().mid(6,2));
        }
        fclose(fp);
    }

    is_eth0_enabled = (system("grep -c INTERFACE0 /etc/rc.d/rc.conf >/dev/null 2>&1") == 0);
    is_eth1_enabled = (system("grep -c INTERFACE1 /etc/rc.d/rc.conf >/dev/null 2>&1") == 0);

    ui->labelMACeth0->setVisible(is_eth0_enabled);
    ui->pushButtonMACeth0_1->setVisible(is_eth0_enabled);
    ui->pushButtonMACeth0_2->setVisible(is_eth0_enabled);
    ui->pushButtonMACeth0_3->setVisible(is_eth0_enabled);
    ui->pushButtonMACeth0_4->setVisible(is_eth0_enabled);
    ui->pushButtonMACeth0_5->setVisible(is_eth0_enabled);
    ui->pushButtonMACeth0_6->setVisible(is_eth0_enabled);
    if (is_eth0_enabled)
    {
        ui->pushButtonMACeth0_1->setText("70");
        ui->pushButtonMACeth0_2->setText("B3");
        ui->pushButtonMACeth0_3->setText("D5");
        ui->pushButtonMACeth0_4->setText("62");
        ui->pushButtonMACeth0_5->setText("");
        ui->pushButtonMACeth0_6->setText("");
        fp = fopen(MAC_ADDRESS_FILE, "r");
        if (fp != NULL)
        {
            char line[32];
            while (fgets(line, 32, fp) != NULL && QString(line).split("=").at(0).compare("MAC0") != 0);
            if (QString(line).split("=").at(0).compare("MAC0") != 0)
            {
                QString mac = QString(line).trimmed().split("=").at(1);
                ui->pushButtonMACeth0_1->setText(mac.split(":").at(0));
                ui->pushButtonMACeth0_2->setText(mac.split(":").at(1));
                ui->pushButtonMACeth0_3->setText(mac.split(":").at(2));
                ui->pushButtonMACeth0_4->setText(mac.split(":").at(3));
                ui->pushButtonMACeth0_5->setText(mac.split(":").at(4));
                ui->pushButtonMACeth0_6->setText(mac.split(":").at(5));
            }
            fclose(fp);
        }
    }

    ui->labelMACeth1->setVisible(is_eth1_enabled);
    ui->pushButtonMACeth1_1->setVisible(is_eth1_enabled);
    ui->pushButtonMACeth1_2->setVisible(is_eth1_enabled);
    ui->pushButtonMACeth1_3->setVisible(is_eth1_enabled);
    ui->pushButtonMACeth1_4->setVisible(is_eth1_enabled);
    ui->pushButtonMACeth1_5->setVisible(is_eth1_enabled);
    ui->pushButtonMACeth1_6->setVisible(is_eth1_enabled);
    if (is_eth1_enabled)
    {
        ui->pushButtonMACeth1_1->setText("70");
        ui->pushButtonMACeth1_2->setText("B3");
        ui->pushButtonMACeth1_3->setText("D5");
        ui->pushButtonMACeth1_4->setText("62");
        ui->pushButtonMACeth1_5->setText("");
        ui->pushButtonMACeth1_6->setText("");
        fp = fopen(MAC_ADDRESS_FILE, "r");
        if (fp != NULL)
        {
            char line[32];
            while (fgets(line, 32, fp) != NULL && QString(line).split("=").at(0).compare("MAC1") != 0);
            if (QString(line).split("=").at(0).compare("MAC1") != 0)
            {
                QString mac = QString(line).trimmed().split("=").at(1);
                ui->pushButtonMACeth1_1->setText(mac.split(":").at(0));
                ui->pushButtonMACeth1_2->setText(mac.split(":").at(1));
                ui->pushButtonMACeth1_3->setText(mac.split(":").at(2));
                ui->pushButtonMACeth1_4->setText(mac.split(":").at(3));
                ui->pushButtonMACeth1_5->setText(mac.split(":").at(4));
                ui->pushButtonMACeth1_6->setText(mac.split(":").at(5));
            }
            fclose(fp);
        }
    }
}

mac_sn::~mac_sn()
{
    delete ui;
}

void mac_sn::on_pushButtonSN_1_clicked()
{
    int value  = 2016, min = 0, max = 2099;
    numpad * dk = new numpad(&value, ui->pushButtonSN_1->text().toInt(), min, max);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(value).arg(min).arg(max));
            delete dk;
            return;
        }
        char valuestr[10];
        sprintf (valuestr, "%.4d", value);
        ui->pushButtonSN_1->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonSN_2_clicked()
{
    int value  = 0, min = 1, max = 12;
    numpad * dk = new numpad(&value, ui->pushButtonSN_2->text().toInt(), min, max);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(value).arg(min).arg(max));
            delete dk;
            return;
        }
        char valuestr[10];
        sprintf (valuestr, "%.2d", value);
        ui->pushButtonSN_2->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonSN_3_clicked()
{
    int value  = 0, min = 0, max = 9999;
    numpad * dk = new numpad(&value, ui->pushButtonSN_3->text().toInt(), min, max);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(value).arg(min).arg(max));
            delete dk;
            return;
        }
        char valuestr[10];
        sprintf (valuestr, "%.4d", value);
        ui->pushButtonSN_3->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}


void mac_sn::on_pushButtonMACeth0_1_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth0_1->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth0_1->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth0_2_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth0_2->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth0_2->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth0_3_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth0_3->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth0_3->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth0_4_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth0_4->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth0_4->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth0_5_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth0_5->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth0_5->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth0_6_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth0_6->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth0_6->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth1_1_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth1_1->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth1_1->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth1_2_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth1_2->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth1_2->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth1_3_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth1_3->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth1_3->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth1_4_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth1_4->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth1_4->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth1_5_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth1_5->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth1_5->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonMACeth1_6_clicked()
{
    int value  = 0, min = 0, max = 0xFF;
    char valuestr[10];
    numpad * dk = new numpad(&value, atoh(ui->pushButtonMACeth1_6->text().toAscii().data()), min, max, input_hex);
    dk->showFullScreen();

    if (dk->exec() == QDialog::Accepted)
    {
        if (min < max && (value < min || value > max))
        {
            QMessageBox::critical(this,tr("Dato non valido"), tr("Il valore '%1' inserito non e' valido.\nIl valore deve essere compreso tra '%2' e '%3'").arg(QString::number(value,16)).arg("00").arg("FF"));
            delete dk;
            return;
        }
        sprintf (valuestr, "%.2X", value);
        ui->pushButtonMACeth1_6->setText(valuestr);
    }
    else
    {
        delete dk;
        return;
    }
}

void mac_sn::on_pushButtonOk_clicked()
{
    FILE * fp;
    if(system("mount -orw,remount /"))
    {
        QMessageBox::critical(this,tr("Read only"), tr("Cannot set the system in read/write"));
        return;
    }
    if (
            ui->pushButtonSN_1->text().length() != 4
            ||
            ui->pushButtonSN_2->text().length() != 2
            ||
            ui->pushButtonSN_3->text().length() <= 0
            )
    {
        QMessageBox::critical(this,tr("Invalid value"), tr("Invalid value for serial number"));
        return;
    }
    fp = fopen(SERIAL_NUMBER_FILE, "w");
    if (fp == NULL)
    {
        QMessageBox::critical(this,tr("Read only"), tr("Cannot write the serial number"));
        return;
    }
    fprintf( fp,
             "%s%s%s\n",
             ui->pushButtonSN_1->text().toAscii().data(),
             ui->pushButtonSN_2->text().toAscii().data(),
             ui->pushButtonSN_3->text().toAscii().data()
             );
    fclose(fp);

    if (
            is_eth0_enabled &&
            (
                ui->pushButtonMACeth0_1->text().length() != 2
                ||
                ui->pushButtonMACeth0_2->text().length() != 2
                ||
                ui->pushButtonMACeth0_3->text().length() != 2
                ||
                ui->pushButtonMACeth0_4->text().length() != 2
                ||
                ui->pushButtonMACeth0_5->text().length() != 2
                ||
                ui->pushButtonMACeth0_6->text().length() != 2
                )
            )
    {
        QMessageBox::critical(this,tr("Invalid value"), tr("Invalid value for eth0 mac address"));
        return;
    }
    if (
            is_eth1_enabled &&
            (
                ui->pushButtonMACeth1_1->text().length() != 2
                ||
                ui->pushButtonMACeth1_2->text().length() != 2
                ||
                ui->pushButtonMACeth1_3->text().length() != 2
                ||
                ui->pushButtonMACeth1_4->text().length() != 2
                ||
                ui->pushButtonMACeth1_5->text().length() != 2
                ||
                ui->pushButtonMACeth1_6->text().length() != 2
                )
            )
    {
        QMessageBox::critical(this,tr("Invalid value"), tr("Invalid value for eth1 mac address"));
        return;
    }
    fp = fopen(MAC_ADDRESS_FILE, "w");
    if (fp == NULL)
    {
        QMessageBox::critical(this,tr("Read only"), tr("Cannot write the serial number"));
        return;
    }
    if (is_eth0_enabled)
    {
        fprintf( fp,
                 "MAC0=%s:%s:%s:%s:%s:%s\n",
                 ui->pushButtonMACeth0_1->text().toAscii().data(),
                 ui->pushButtonMACeth0_2->text().toAscii().data(),
                 ui->pushButtonMACeth0_3->text().toAscii().data(),
                 ui->pushButtonMACeth0_4->text().toAscii().data(),
                 ui->pushButtonMACeth0_5->text().toAscii().data(),
                 ui->pushButtonMACeth0_6->text().toAscii().data()
                 );
    }
    if (is_eth1_enabled)
    {
        fprintf( fp,
                 "MAC1=%s:%s:%s:%s:%s:%s\n",
                 ui->pushButtonMACeth1_1->text().toAscii().data(),
                 ui->pushButtonMACeth1_2->text().toAscii().data(),
                 ui->pushButtonMACeth1_3->text().toAscii().data(),
                 ui->pushButtonMACeth1_4->text().toAscii().data(),
                 ui->pushButtonMACeth1_5->text().toAscii().data(),
                 ui->pushButtonMACeth1_6->text().toAscii().data()
                 );
    }
    fclose(fp);

    system("mount -oro,remount /");
    system("sync");
    system("/etc/rc.d/init.d/network restart");
}

void mac_sn::on_pushButtonCancel_clicked()
{
    exit (0);
}
