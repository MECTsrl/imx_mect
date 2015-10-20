#-------------------------------------------------
#
# Project created by QtCreator 2012-07-24T16:18:41
#
#-------------------------------------------------

QT       += core gui

TARGET = Qt4CTestSuiteBis
TEMPLATE = app

DEPENDPATH += .

INCLUDEPATH += .\
.. \
../inc \
../inc.fc

LIBPATH += ../lib

LIBS += -lvisLib \
-losKernel \
-losShared


HEADERS  += Qt4CTestSuiteBis.h \
			picture.h \
			fc_comunication.h

FORMS    += \
    Qt4CTestSuiteBis.ui \
    picture.ui

SOURCES += main.cpp\
		   Qt4CTestSuiteBis.cpp \
		   picture.cpp \
		   fc_comunication.cpp



target.path += ../bin 
INSTALLS += target

