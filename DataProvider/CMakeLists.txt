cmake_minimum_required(VERSION 3.13)
project(DataProvider)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
		DataProvider.h
		DataProvider.cpp
		DataProxy.h
		DataProxy.cpp
		IDataProvider.h
		IDataProxy.h
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
	Qt5::Core
)
