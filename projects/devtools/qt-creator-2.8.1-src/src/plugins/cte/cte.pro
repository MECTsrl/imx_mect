include(../../qtcreatorplugin.pri)

HEADERS += \
    cteplugin.h \
    parser.h \
    ctedit.h \
    utils.h

SOURCES += \
    cteplugin.cpp \
    parser.c \
    ctedit.cpp \
    utils.cpp

FORMS += \
    ctedit.ui \

LIBS += \
    -L../projectexplorer -lProjectExplorer
