#include <QtGui/QApplication>
#include <QWSServer>
#include "setuptime.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	QWSServer::setCursorVisible(false);
    
	setupTime w;
    w.showFullScreen();
    
    return a.exec();
}
