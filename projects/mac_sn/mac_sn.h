#ifndef MAC_SN_H
#define MAC_SN_H

#include <QWidget>

#define SERIAL_NUMBER_FILE "/etc/serial.conf"
#define MAC_ADDRESS_FILE   "/etc/mac.conf"

namespace Ui {
class mac_sn;
}

class mac_sn : public QWidget
{
    Q_OBJECT
    
public:
    explicit mac_sn(QWidget *parent = 0);
    ~mac_sn();
    
private slots:
    void on_pushButtonSN_1_clicked();
    void on_pushButtonSN_2_clicked();
    void on_pushButtonSN_3_clicked();

    void on_pushButtonMACeth0_1_clicked();
    void on_pushButtonMACeth0_2_clicked();
    void on_pushButtonMACeth0_3_clicked();
    void on_pushButtonMACeth0_4_clicked();
    void on_pushButtonMACeth0_5_clicked();
    void on_pushButtonMACeth0_6_clicked();

    void on_pushButtonMACeth1_1_clicked();
    void on_pushButtonMACeth1_2_clicked();
    void on_pushButtonMACeth1_3_clicked();
    void on_pushButtonMACeth1_4_clicked();
    void on_pushButtonMACeth1_5_clicked();
    void on_pushButtonMACeth1_6_clicked();

    void on_pushButtonOk_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::mac_sn *ui;
    bool is_eth0_enabled;
    bool is_eth1_enabled;
};

#endif // MAC_SN_H
