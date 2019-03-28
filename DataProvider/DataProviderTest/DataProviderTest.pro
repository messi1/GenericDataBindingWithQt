TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core


INCLUDEPATH += \
               .. \
               ../..

PRE_TARGETDEPS += ../../RequestData/libRequestDataLib.a \
                  ../libDataProviderLib.a

LIBS += -L../ -lDataProviderLib \
        -L../../RequestData -lRequestDataLib \
        -L/usr/local/lib -lgtest

HEADERS += \
    tst_DataProxy.h \
    tst_DataProvider.h \
    TestValues.h \
    MockConnector.h \
    MockDataProxy.h \
    MockDataProvider.h \
    MockDataClientManager.h

SOURCES += \
        main.cpp \
    TestValues.cpp
