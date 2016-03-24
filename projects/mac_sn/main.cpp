#include <QtGui/QApplication>
#include <QWSServer>
#include <stdio.h>
#include "mac_sn.h"

/**
 * @brief main
 */
int main(int argc, char *argv[])
{
    FILE * fpsn, * fpmac;

    fpsn = fopen(SERIAL_NUMBER_FILE, "r");
    fpmac = fopen(MAC_ADDRESS_FILE, "r");

    if (fpsn && fpmac)
    {
        fclose(fpsn);
        fclose(fpmac);
        return 0;
    }

    QApplication a(argc, argv);

    /* set the cursor as invisible */
    QWSServer::setCursorVisible(false);

    mac_sn w;
    w.showFullScreen();
    
    return a.exec();
}
