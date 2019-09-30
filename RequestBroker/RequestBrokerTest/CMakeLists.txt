cmake_minimum_required(VERSION 3.13)
project(RequestBrokerTest)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp
)
