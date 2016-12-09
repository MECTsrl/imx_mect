include(../../qtcreatorplugin.pri)

HEADERS += \
    cteplugin.h \
    parser.h \
    ctedit.h \

SOURCES += \
    cteplugin.cpp \
    parser.c \
    ctedit.cpp \

FORMS += \
    ctedit.ui \

LIBS += \
    -L../projectexplorer -lProjectExplorer
