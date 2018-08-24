TARGET         = DemoApp
QT             = core gui widgets xml
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../


LIBS += -L../DataBinding  -lDataBindingLib
LIBS += -L../DataProvider -lDataProviderLib
LIBS += -L../RequestData  -lRequestDataLib


HEADERS += BaseFrame.h


SOURCES += main.cpp \
           BaseFrame.cpp
