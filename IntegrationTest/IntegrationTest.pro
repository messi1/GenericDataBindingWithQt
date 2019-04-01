TARGET         = IntegrationTest
QT             = core
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../

INCLUDEPATH += \
               .. \
               ../..

PRE_TARGETDEPS += ../RequestData/libRequestDataLib.a \
                  ../DataBinding/libDataBindingLib.a \
                  ../DataProvider/libDataProviderLib.a

LIBS += -L../DataBinding  -lDataBindingLib \
        -L../DataProvider -lDataProviderLib \
        -L../RequestData  -lRequestDataLib \
        -L/usr/local/lib  -lgtest

HEADERS += \
    ../DataProvider/DataProviderTest/TestValues.h \
    tst_MultiRequests.h \
    tst_RequestWithDeletedManager.h \
    tst_CopyRequest.h

SOURCES += \
        main.cpp \
    ../DataProvider/DataProviderTest/TestValues.cpp
