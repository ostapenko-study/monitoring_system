INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/inspector_common.cpp \
    $$PWD/process/PID_generator.cpp \
    $$PWD/stat/ProcessCpuStat.cpp \
    $$PWD/stat/ProcessMemStat.cpp \
    $$PWD/stat/StatToJson.cpp \
    $$PWD/stat/SystemCpuStat.cpp \
    $$PWD/stat/SystemMemInfo.cpp \
    $$PWD/stat/TopStat.cpp

HEADERS += \
    $$PWD/inspector_common.h \
    $$PWD/process/PID_generator.h \
    $$PWD/stat/ProcessCpuStat.h \
    $$PWD/stat/ProcessMemStat.h \
    $$PWD/stat/StatToJson.h \
    $$PWD/stat/SystemCpuStat.h \
    $$PWD/stat/SystemMemInfo.h \
    $$PWD/stat/TopStat.h
