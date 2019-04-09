TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core


INCLUDEPATH += \
               .. \
               ../..

LIBS += -L../ -lRequestDataLib \
        -L/usr/local/lib -lgtest

HEADERS += \
    tst_RequestData.h \
    TestValues.h

SOURCES += \
    main.cpp

