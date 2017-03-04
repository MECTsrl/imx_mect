TEMPLATE = app
LANGUAGE = C
TARGET = ctc

DESTDIR = ../../../bin

SOURCES += ctc.c

HEADERS += ctc.h

LIBS += -lcsv


PROJECTNAME = Cross Table Compiler

# Install the target.
target.path = $$QTC_PREFIX/bin
INSTALLS += target
