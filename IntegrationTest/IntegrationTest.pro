TARGET         = IntegrationTest
QT             = core
QMAKE_CXXFLAGS = -Wextra -Wnon-virtual-dtor -ggdb -std=gnu++11
CONFIG  += c++14

INCLUDEPATH += ../

INCLUDEPATH += \
               .. \
               ../..

PRE_TARGETDEPS += ../RequestResponseData/libRequestResponseDataLib.a \
                  ../DataBinding/libDataBindingLib.a \
                  ../DataProvider/libDataProviderLib.a

LIBS += -L../DataBinding  -lDataBindingLib \
        -L../DataProvider -lDataProviderLib \
        -L../RequestResponseData  -lRequestResponseDataLib \
        -L/usr/local/lib  -lgtest

HEADERS += \
    ../RequestResponseData/RequestResponseDataTest/TestRequestValues.h \
    ../RequestResponseData/RequestResponseDataTest/TestResponseValues.h \
    tst_MultiRequests.h \
    tst_RequestWithDeletedManager.h \
    tst_CopyRequest.h \
    MockConnector.h

SOURCES += \
    main.cpp \
    ../RequestResponseData/RequestResponseDataTest/TestRequestValues.cpp \
    ../RequestResponseData/RequestResponseDataTest/TestResponseValues.cpp \
