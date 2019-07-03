TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core


INCLUDEPATH += \
               .. \
               ../..

LIBS += -L../ -lRequestResponseDataLib \
        -L/usr/local/lib -lgtest


HEADERS += \
    TestRequestValues.h \
    TestResponseValues.h \
    tst_RequestData.h \
    tst_ResponseData.h

SOURCES += \
    TestRequestValues.cpp \
    TestResponseValues.cpp \
    main.cpp
