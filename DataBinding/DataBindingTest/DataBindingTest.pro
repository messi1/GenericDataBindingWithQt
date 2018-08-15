include(gtest_dependency.pri)

TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core

INCLUDEPATH += \
               .. \
               ../..

LIBS += -L../ -lDataBindingLib \
        -L../../RequestData/ -lRequestDataLib

HEADERS += \
    tst_DataClient.h \
    tst_DataClientManager.h \
    MockDataClientManager.h \
    TestDataClient.h \
    MockProxy.h


SOURCES += \
        main.cpp

DISTFILES += \
    target.mk
