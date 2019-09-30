TEMPLATE = lib
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

SOURCES += \
    TestRequestValues.cpp \
    TestResponseValues.cpp
