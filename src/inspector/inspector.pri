INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(../websockets/websockets.pri)

SOURCES += \
    $$PWD/CommandHandler.cpp \
    $$PWD/inspector_common.cpp \
    $$PWD/network/network_scanner.cpp \
    $$PWD/process/PID_generator.cpp \
    $$PWD/ssh_config.cpp \
    $$PWD/stat/MainStat.cpp \
    $$PWD/stat/ProcessCpuStat.cpp \
    $$PWD/stat/ProcessMemStat.cpp \
    $$PWD/stat/StatToJson.cpp \
    $$PWD/stat/SystemCpuStat.cpp \
    $$PWD/stat/SystemMemInfo.cpp

HEADERS += \
    $$PWD/CommandHandler.h \
    $$PWD/ssh_config.h \
    $$PWD/inspector_common.h \
    $$PWD/network/network_scanner.h \
    $$PWD/process/PID_generator.h \
    $$PWD/stat/MainStat.h \
    $$PWD/stat/ProcessCpuStat.h \
    $$PWD/stat/ProcessMemStat.h \
    $$PWD/stat/StatToJson.h \
    $$PWD/stat/SystemCpuStat.h \
    $$PWD/stat/SystemMemInfo.h
