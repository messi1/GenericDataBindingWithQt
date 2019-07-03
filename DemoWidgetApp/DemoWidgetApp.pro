TARGET         = DemoWidgetApp
QT             = core gui widgets
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../


LIBS += -L../DataBinding  -lDataBindingLib
LIBS += -L../DataProvider -lDataProviderLib
LIBS += -L../RequestResponseData  -lRequestResponseDataLib


HEADERS += DataClientManagers/BaseFrame.h \
    DataClients/DCPushButton.h \
    DataClients/DCCheckBox.h \
    DataClients/DCLabel.h \
    DataClients/DCComboBox.h \
    DataClients/DCTextEdit.h \
    DataClients/DCLineEdit.h


SOURCES += main.cpp \
    DataClientManagers/BaseFrame.cpp \
    DataClients/DCPushButton.cpp \
    DataClients/DCCheckBox.cpp \
    DataClients/DCLabel.cpp \
    DataClients/DCComboBox.cpp \
    DataClients/DCTextEdit.cpp \
    DataClients/DCLineEdit.cpp \
    ../RequestResponseData/RequestResponseDataTest/TestRequestValues.cpp \
    ../RequestResponseData/RequestResponseDataTest/TestResponseValues.cpp
