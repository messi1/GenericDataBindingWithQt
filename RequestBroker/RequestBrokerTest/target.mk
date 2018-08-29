# identify the qt5 repository by searching for a file that is unique for qt5
QT5_REP_DIR := $(call select_from_repositories,lib/import/import-qt5.inc)
QT5_REP_DIR := $(realpath $(dir $(QT5_REP_DIR))../..)

GTEST_DIR := $(call select_from_ports,googletest)/src/lib/googletest/googletest
GMOCK_DIR := $(call select_from_ports,googletest)/src/lib/googletest/googlemock

# don't auto-include the QMake project file
QMAKE_PROJECT_FILE=

TARGET = gtest_RequestBrokerLib

include $(QT5_REP_DIR)/src/app/qt5/tmpl/target_defaults.inc
include $(QT5_REP_DIR)/src/app/qt5/tmpl/target_final.inc

include $(call select_from_repositories,run/my-import-qt5.inc)


INC_DIR += $(REP_DIR)/src/UiNewGui/
INC_DIR += $(REP_DIR)/src/UiNewGui/DataBinding
INC_DIR += $(REP_DIR)/../UiBroker/
QT5_INC_DIR += $(REP_DIR)/src/UiNewGui/
INC_DIR += $(GTEST_DIR)
INC_DIR += $(GTEST_DIR)/include
INC_DIR += $(GMOCK_DIR)
INC_DIR += $(GMOCK_DIR)/include

SRC_CC += main.cpp

LIBS += qt5_component gtest RequestDataLib



CC_CXX_WARN_STRICT =
