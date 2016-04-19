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

    int width = 1480;
    int height = 1272;
    int rotation = 0;
    char vncString[256];

    FILE * fp = fopen ("/sys/class/graphics/fb0/virtual_size", "r");
    if (fp)
    {
        fscanf(fp, "%d,%d", &width, &height);
        fclose(fp);
    }

    sprintf(vncString, "Multi: VNC:0:size=%dx%d Transformed:rot%d", width, height, rotation);

    int myargc = argc + 4;
    char *myargv[] =
    {
        argv[0],
        strdup("-qws"),
        strdup("-display"),
        vncString
    };

    QApplication a(myargc, myargv);

    /* set the cursor as invisible */
    QWSServer::setCursorVisible(false);

    mac_sn w;
    w.showFullScreen();
    
    return a.exec();
}
