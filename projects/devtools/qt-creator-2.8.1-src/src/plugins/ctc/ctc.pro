TEMPLATE = app
LANGUAGE = C
TARGET = ctc

DESTDIR = ../../../bin

SOURCES += ctc.c

HEADERS += ctc.h

LIBS += -lcsv


PROJECTNAME = Cross Table Compiler

# TODO: This should be enough to install the target...
target.path = $$[QT_INSTALL_BINS]
# ...but this is actually required to install it in the RIGHT place.
target.extra = install -m 755 $$DESTDIR/$$TARGET $$[QT_INSTALL_BINS]
INSTALLS += target
