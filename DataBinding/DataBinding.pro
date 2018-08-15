TEMPLATE       = lib
TARGET         = DataBindingLib
QT             = core
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG        += c++14
CONFIG        += staticlib


INCLUDEPATH += \
               .. \


HEADERS   += \
    DataClient.h \
    DataClientManager.h \
    IDataClient.h \
    IDataClientManager.h

SOURCES   += \
    DataClient.cpp \
    DataClientManager.cpp

# They have to be here otherwise the shitty Genode build system will fail
OTHER_FILES += \


DISTFILES += \
    LICENSE.txt
