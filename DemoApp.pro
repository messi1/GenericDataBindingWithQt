TARGET         = DemoApp
QT             = core gui widgets xml
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ./

SOURCES   += main.cpp

LIBS += -L./DataBinding  -lDataBindingLib
LIBS += -L./DataProvider -lDataProviderLib
LIBS += -L./RequestData  -lRequestDataLib


OTHER_FILES += LICENSE.txt \

