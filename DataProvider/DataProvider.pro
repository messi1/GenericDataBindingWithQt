TEMPLATE       = lib
TARGET         = DataProviderLib
QT             = core
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG        += c++14
CONFIG        += staticlib

target.path = ../libs
INSTALLS += target

INCLUDEPATH += ../ \


HEADERS   += \
    DataProvider.h \
    DataProxy.h

SOURCES   += \
    DataProvider.cpp \
    DataProxy.cpp

# They have to be here otherwise the shitty Genode build system will fail
OTHER_FILES += \
    IDataProvider.h \
    IDataProxy.h

DISTFILES += \
    ../../../lib/mk/DataProviderLib.mk


