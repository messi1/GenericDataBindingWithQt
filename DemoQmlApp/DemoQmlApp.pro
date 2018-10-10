TARGET         = DemoQmlApp
QT             = core gui qml quick
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../

LIBS += -L../DataBinding  -lDataBindingLib
LIBS += -L../DataProvider -lDataProviderLib
LIBS += -L../RequestData  -lRequestDataLib

SOURCES += \
    main.cpp \
    DCLineEdit.cpp \
    DCComponent.cpp

HEADERS += \
    DCLineEdit.h \
    DCComponent.h

DISTFILES += \
    qml/MainWindow.qml
