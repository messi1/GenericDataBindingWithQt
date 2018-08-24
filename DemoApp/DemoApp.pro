TARGET         = DemoApp
QT             = core gui widgets xml
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../


LIBS += -L../DataBinding  -lDataBindingLib
LIBS += -L../DataProvider -lDataProviderLib
LIBS += -L../RequestData  -lRequestDataLib


HEADERS += DataClientManagers/BaseFrame.h \
    DataClients/PushButton.h \
    DataClients/CheckBox.h \
    DataClients/Label.h \
    DataClients/ComboBox.h \
    DataClients/TextEdit.h \
    DataClients/LineEdit.h


SOURCES += main.cpp \
           DataClientManagers/BaseFrame.cpp \
    DataClients/PushButton.cpp \
    DataClients/CheckBox.cpp \
    DataClients/Label.cpp \
    DataClients/ComboBox.cpp \
    DataClients/TextEdit.cpp \
    DataClients/LineEdit.cpp
