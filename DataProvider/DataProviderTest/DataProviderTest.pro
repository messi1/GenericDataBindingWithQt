include(gtest_dependency.pri)


TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core


INCLUDEPATH += \
               .. \
               ../..

LIBS += -L../ -lDataProviderLib \
        -L../../RequestData -lRequestDataLib

HEADERS += \
    tst_DataProxy.h \
    tst_DataProvider.h \
    TestValues.h \
    MockConnector.h \
    MockDataProxy.h \
    MockDataProvider.h \
    MockDataClientManager.h

SOURCES += \
        main.cpp

DISTFILES += \
    target.mk
