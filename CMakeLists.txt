cmake_minimum_required(VERSION 3.22)
project(BemaniMetadataParser)

set(CMAKE_CXX_STANDARD 20)

include(cmake/get_cpm.cmake)

add_subdirectory(ChartManager)

add_executable(BemaniMetadataParser main.cpp)

target_link_libraries(BemaniMetadataParser ChartManager)