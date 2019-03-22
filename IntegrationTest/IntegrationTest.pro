TARGET         = IntegrationTest
QT             = core gui widgets
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../

INCLUDEPATH += \
               .. \
               ../..

PRE_TARGETDEPS += ../RequestData/libRequestDataLib.a \
                  ../DataBinding/libDataBindingLib.a

LIBS += -L../DataBinding  -lDataBindingLib \
        -L../DataProvider -lDataProviderLib \
        -L../RequestData  -lRequestDataLib \
        -L/usr/local/lib  -lgtest \
        -L/usr/lib/x86_64-linux-gnu/ -lcurl

HEADERS += \
    ../DataProvider/DataProviderTest/TestValues.h \
    tst_MultiRequests.h \
    tst_RequestWithDeletedManager.h

SOURCES += \
        main.cpp \
    ../DataProvider/DataProviderTest/TestValues.cpp
