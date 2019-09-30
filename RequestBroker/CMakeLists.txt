cmake_minimum_required(VERSION 3.13)
project(RequestBroker)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    IConnector.h
    RequestBroker.h
    RequestBroker.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
)

