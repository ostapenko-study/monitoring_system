QT += websockets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/ClientConfig.cpp \
    $$PWD/Common.cpp \
    $$PWD/ServerConfig.cpp \
    $$PWD/WebsocketClient.cpp \
    $$PWD/WebsocketServer.cpp

HEADERS += \
    $$PWD/ClientConfig.h \
    $$PWD/Common.h \
    $$PWD/ServerConfig.h \
    $$PWD/WebsocketClient.h \
    $$PWD/WebsocketServer.h
