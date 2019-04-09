TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core

INCLUDEPATH += \
               .. \
               ../..

LIBS += -L../ -lDataBindingLib \
        -L../../RequestData/ -lRequestDataLib \
        -L/usr/local/lib -lgtest

PRE_TARGETDEPS += ../../RequestData/libRequestDataLib.a \
                  ../libDataBindingLib.a

HEADERS += \
    tst_DataClient.h \
    tst_DataClientManager.h \
    MockDataClientManager.h \
    TestDataClient.h \
    MockDataProxy.h


SOURCES += \
        main.cpp
