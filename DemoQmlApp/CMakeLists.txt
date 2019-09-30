cmake_minimum_required(VERSION 3.13)
project(DemoQmlApp)

add_executable(${PROJECT_NAME})

find_package(Qt5 COMPONENTS Quick Qml REQUIRED)

target_sources(${PROJECT_NAME}
    PRIVATE
        DCComponent.h
        DCLineEdit.h
        DCComponent.cpp
        DCLineEdit.cpp
        main.cpp
        qml/MainWindow.qml
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        Qt5::Qml
        Qt5::Quick
        RequestResponseData
        DataProvider
        DataBinding
        TestDataValues
)
