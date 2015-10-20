#-------------------------------------------------
#
# Project created by QtCreator 2013-04-22T12:56:15
#
#-------------------------------------------------

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_LFLAGS_RELEASE -= -O1

#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg

TEMPLATE = app

TARGET = setup_time

INCLUDEPATH += .\
    $(RFSDIR)/usr/src/linux/include \
    $(RFSDIR)/usr/include


QT       += core gui

HEADERS  += setuptime.h

FORMS    += setuptime.ui

SOURCES += main.cpp\
        setuptime.cpp

RESOURCES += \
    hmi.qrc

