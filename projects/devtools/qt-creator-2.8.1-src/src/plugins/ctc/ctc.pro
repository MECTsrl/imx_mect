TEMPLATE = app
LANGUAGE = C
TARGET = ctc

DESTDIR = ../../../bin

SOURCES += \
    ctc.c \

HEADERS += \
    ctc.h \

LIBS += \
    -lcsv


PROJECTNAME = \
    Cross Table Compiler

# TODO: This should be enough to install the target in the proper place...
target.path = $$[QT_INSTALL_BINS]
# ...but this is actually required to install in the right palce.
unix:target.extra = install -m 755 $$DESTDIR/$$TARGET $$[QT_INSTALL_BINS]
INSTALLS += target
