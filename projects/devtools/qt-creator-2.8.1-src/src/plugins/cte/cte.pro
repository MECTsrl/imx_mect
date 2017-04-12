include(../../qtcreatorplugin.pri)

HEADERS += \
    cteplugin.h \
    parser.h \
    ctedit.h \
    utils.h \  
    cteerrdef.h \
    cteerrorlist.h \
    mectsettings.h \
    trendeditor.h

SOURCES += \
    cteplugin.cpp \
    parser.c \
    ctedit.cpp \
    utils.cpp \  
    cteerrorlist.cpp \
    mectsettings.cpp \
    trendeditor.cpp

FORMS += \
    ctedit.ui \  
    cteerrorlist.ui \
    mectsettings.ui \
    trendeditor.ui

LIBS += \
    -L../projectexplorer -lProjectExplorer

RESOURCES += \
    qtc.qrc

OTHER_FILES +=
