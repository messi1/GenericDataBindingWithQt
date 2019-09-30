cmake_minimum_required(VERSION 3.13)
project(DemoWidgetApp)

add_executable(${PROJECT_NAME})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_sources(${PROJECT_NAME}
    PRIVATE
        DataClientManagers/BaseFrame.h
        DataClientManagers/BaseFrame.cpp
        DataClients/DCCheckBox.h
        DataClients/DCComboBox.h
        DataClients/DCLabel.h
        DataClients/DCLineEdit.h
        DataClients/DCPushButton.h
        DataClients/DCTextEdit.h
        DataClients/DCCheckBox.cpp
        DataClients/DCComboBox.cpp
        DataClients/DCLabel.cpp
        DataClients/DCLineEdit.cpp
        DataClients/DCPushButton.cpp
        DataClients/DCTextEdit.cpp
        main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        Qt5::Widgets
        RequestResponseData
        DataProvider
        DataBinding
        TestDataValues
)
