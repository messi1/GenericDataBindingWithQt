TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core


INCLUDEPATH += \
               .. \
               ../.. \
               ../../RequestResponseData/ \
               ../../RequestResponseData/RequestResponseDataTest/

PRE_TARGETDEPS += ../../RequestResponseData/libRequestResponseDataLib.a \
                  ../libDataProviderLib.a

LIBS += -L../ -lDataProviderLib \
        -L../../RequestResponseData -lRequestResponseDataLib \
        -L/usr/local/lib -lgtest

HEADERS += \
    ../../RequestResponseData/RequestResponseDataTest/TestRequestValues.h \
    ../../RequestResponseData/RequestResponseDataTest/TestResponseValues.h \
    tst_DataProxy.h \
    tst_DataProvider.h \
    MockConnector.h \
    MockDataProxy.h \
    MockDataProvider.h \
    MockDataClientManager.h

SOURCES += \
    ../../RequestResponseData/RequestResponseDataTest/TestRequestValues.cpp \
    ../../RequestResponseData/RequestResponseDataTest/TestResponseValues.cpp \
    main.cpp
