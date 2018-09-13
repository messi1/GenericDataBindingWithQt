TARGET         = DemoQmlApp
QT             = core gui qml quick
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../

SOURCES += \
    main.cpp
