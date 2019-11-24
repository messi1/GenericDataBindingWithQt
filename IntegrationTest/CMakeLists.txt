cmake_minimum_required(VERSION 3.13)
project(IntegrationTest)

add_executable(${PROJECT_NAME})

find_package(Qt5 COMPONENTS Test REQUIRED)

target_sources(${PROJECT_NAME}
    PRIVATE
        MockConnector.h
        tst_CopyRequest.h
        tst_MultiRequests.h
        tst_RequestWithDeletedManager.h

        main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        Qt5::Test
        GTest::GTest
        RequestResponseData
        DataBinding
        DataProvider
        TestDataValues
)
