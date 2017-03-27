include(../../qtcreatorplugin.pri)

HEADERS += \
    cteplugin.h \
    parser.h \
    ctedit.h \
    utils.h \  
    cteerrdef.h \
    cteerrorlist.h

SOURCES += \
    cteplugin.cpp \
    parser.c \
    ctedit.cpp \
    utils.cpp \  
    cteerrorlist.cpp

FORMS += \
    ctedit.ui \  
    cteerrorlist.ui

LIBS += \
    -L../projectexplorer -lProjectExplorer

RESOURCES += \
    qtc.qrc

OTHER_FILES +=
