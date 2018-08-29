include(gtest_dependency.pri)

TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core

INCLUDEPATH += \
               .. \
               ../..

LIBS += -L../../RequestData/ -lRequestDataLib

HEADERS +=


SOURCES += \
        main.cpp

DISTFILES += \
    target.mk
