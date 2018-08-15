include(gtest_dependency.pri)


TEMPLATE = app
CONFIG  += console c++14
CONFIG  -= app_bundle
QT      += testlib core


INCLUDEPATH += \
               .. \
               ../..

LIBS += -L../ -lRequestDataLib

HEADERS += \
    tst_RequestData.h \
    TestValues.h

SOURCES += \
    main.cpp

DISTFILES += \
    gtest_dependency.pri
