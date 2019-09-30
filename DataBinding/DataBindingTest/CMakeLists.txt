cmake_minimum_required(VERSION 3.13)
project(DataBindingTest)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        MockDataClientManager.h
        MockDataProxy.h
        TestDataClient.h
        tst_DataClient.h
        tst_DataClientManager.h
        main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        GTest::GTest
        DataBinding
        RequestResponseData
)
