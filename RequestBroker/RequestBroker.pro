TEMPLATE       = lib
TARGET         = DataProviderLib
QT             = core
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG        += c++14
CONFIG        += staticlib

INCLUDEPATH += ../

HEADERS += \
    IConnector.h \
    RequestBroker.h

SOURCES += \
    RequestBroker.cpp
