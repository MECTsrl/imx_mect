#include <QtGui/QApplication>
#include "Qt4CTestSuiteBis.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt4CTestSuiteBis w;
    w.showFullScreen();

    return a.exec();
}
