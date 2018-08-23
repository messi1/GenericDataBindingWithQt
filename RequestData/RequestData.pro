TEMPLATE       = lib
TARGET         = RequestDataLib
QT             = core
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG        += c++14
CONFIG        += staticlib

target.path = ../libs
INSTALLS += target

INCLUDEPATH += .. \

HEADERS += RequestData.h \
    RequestData.h \
    RequestCommand.h

SOURCES += RequestData.cpp \
    RequestCommand.cpp
