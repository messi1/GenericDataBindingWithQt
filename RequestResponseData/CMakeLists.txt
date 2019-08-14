cmake_minimum_required(VERSION 3.13)
project(RequestResponseData)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
		RequestCommand.h
		RequestCommand.cpp
		RequestData.h
		RequestData.cpp
		ResponseData.h
		ResponseData.cpp
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
	Qt5::Core
)

