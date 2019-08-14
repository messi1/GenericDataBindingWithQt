cmake_minimum_required(VERSION 3.13)
project(DataBinding)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
		DataClient.h
		DataClient.cpp
		DataClientManager.h
		DataClientManager.cpp
		IDataClient.h
		IDataClientManager.h
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
	Qt5::Core
)
