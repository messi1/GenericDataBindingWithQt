TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core

INCLUDEPATH += \
               .. \
               ../.. \
               ../../RequestResponseData/

PRE_TARGETDEPS += ../../RequestResponseData/libRequestResponseDataLib.a \
                  ../libDataBindingLib.a

LIBS += -L../ -lDataBindingLib \
        -L../../RequestResponseData/ -lRequestResponseDataLib \
        -L/usr/local/lib -lgtest

HEADERS += \
    tst_DataClient.h \
    tst_DataClientManager.h \
    MockDataClientManager.h \
    TestDataClient.h \
    MockDataProxy.h


SOURCES += \
        main.cpp
