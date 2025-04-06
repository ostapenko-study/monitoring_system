QT += websockets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/AgentConfig.cpp \
    $$PWD/ClientConfig.cpp \
    $$PWD/ServerConfig.cpp \
    $$PWD/WebsocketClient.cpp \
    $$PWD/WebsocketServer.cpp \
    $$PWD/websockets_common.cpp

HEADERS += \
    $$PWD/AgentConfig.h \
    $$PWD/ClientConfig.h \
    $$PWD/ServerConfig.h \
    $$PWD/WebsocketClient.h \
    $$PWD/WebsocketServer.h \
    $$PWD/websockets_common.h
