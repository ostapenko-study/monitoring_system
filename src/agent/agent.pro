QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../websockets/websockets.pri)

SOURCES += \
        AgentController.cpp \
        AgentWorker.cpp \
        common.cpp \
        main.cpp \
        process/PID_generator.cpp \
        stat/ProcessCpuStat.cpp \
        stat/ProcessMemStat.cpp \
        stat/StatToJson.cpp \
        stat/SystemCpuStat.cpp \
        stat/SystemMemInfo.cpp \
        stat/TopStat.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AgentController.h \
    AgentWorker.h \
    common.h \
    process/PID_generator.h \
    stat/ProcessCpuStat.h \
    stat/ProcessMemStat.h \
    stat/StatToJson.h \
    stat/SystemCpuStat.h \
    stat/SystemMemInfo.h \
    stat/TopStat.h
