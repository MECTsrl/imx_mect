#include <QtGui/QApplication>
#include <QWSServer>
#include <stdio.h>
#include "sdcard.h"

/**
 * @brief main
 */
int main(int argc, char *argv[])
{

    int     width = 1480;
    int     height = 1272;
    int     rotation = 0;
    char    vncString[256];
    bool    isExt3 = false;

    FILE * fp = fopen ("/sys/class/graphics/fb0/virtual_size", "r");
    if (fp)
    {
        fscanf(fp, "%d,%d", &width, &height);
        fclose(fp);
    }

    // preparing VNC String
    sprintf(vncString, "Multi: VNC:0:size=%dx%d Transformed:rot%d", width, height, rotation);

    // Param 1 == 1 ---> IsExt3
    if (argc > 2)  {
        if (strcmp(argv[1], "1") == 0)  {
            isExt3 = true;
        }
    }

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

    sdcard w(isExt3);
    w.showFullScreen();
    
    return a.exec();
}
