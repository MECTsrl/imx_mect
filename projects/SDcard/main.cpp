#include <QtGui/QApplication>
#include <QWSServer>
#include "sdcard.h"

/**
 * @brief main
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* set the cursor as invisible */
    QWSServer::setCursorVisible(false);

    sdcard w;
    w.showFullScreen();
    
    return a.exec();
}
