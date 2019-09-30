cmake_minimum_required(VERSION 3.13)
project(GenericDataBinding)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(GTest)

add_subdirectory(DataBinding)
add_subdirectory(DataBinding/DataBindingTest)
add_subdirectory(DataProvider)
add_subdirectory(DataProvider/DataProviderTest)
add_subdirectory(RequestBroker)
add_subdirectory(RequestBroker/RequestBrokerTest)
add_subdirectory(RequestResponseData)
add_subdirectory(RequestResponseData/TestDataValues)
add_subdirectory(RequestResponseData/RequestResponseDataTest)
add_subdirectory(IntegrationTest)
add_subdirectory(DemoWidgetApp)

add_custom_target(Diagram SOURCES   doc/ClassDiagram.png  doc/ClassDiagram.uml)
