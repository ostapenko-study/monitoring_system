QT += websockets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/ClientConfig.cpp \
    $$PWD/Common.cpp \
    $$PWD/WebsocketClient.cpp

HEADERS += \
    $$PWD/ClientConfig.h \
    $$PWD/Common.h \
    $$PWD/WebsocketClient.h
