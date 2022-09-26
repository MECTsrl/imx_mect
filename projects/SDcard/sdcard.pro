#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T12:27:21
#
#-------------------------------------------------

QT       += core gui

TARGET = SDcard

DEFINES +=  MECT_BUILD_MAJOR=\"$(MECT_BUILD_MAJOR)\" \
            MECT_BUILD_MINOR=\"$(MECT_BUILD_MINOR)\" \
            MECT_BUILD_BUILD=\"$(MECT_BUILD_BUILD)\"

TEMPLATE = app

INCLUDEPATH += \
    $$(DEV_IMAGE)/usr/include

LIBS += \
    -L$$(DEV_IMAGE)/usr/lib


SOURCES += main.cpp\
        sdcard.cpp

HEADERS  += sdcard.h

FORMS    += sdcard.ui

target.path = /local/root

INSTALLS += target
