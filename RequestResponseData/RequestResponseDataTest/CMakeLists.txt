cmake_minimum_required(VERSION 3.13)
project(RequestResponseDataTest)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    tst_ResponseData.h
    tst_RequestData.h
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        RequestResponseData
        TestDataValues
        ${GTEST_LIBRARIES}
        pthread
)

