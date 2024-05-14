cmake_minimum_required(VERSION 3.22)
project(BemaniMetadataParser)

set(CMAKE_CXX_STANDARD 20)
set(wxBUILD_SHARED OFF)

include(cmake/CPM.cmake)

add_subdirectory(Parser)

CPMAddPackage("gh:wxWidgets/wxWidgets@3.2.4")

if(${MSVC})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:WinMainCRTStartup")
endif()

add_executable(BemaniMetadataParser main.cpp
        UI/App.cpp
        UI/App.hpp
        UI/Frames/HomeFrame.cpp
        UI/Frames/HomeFrame.hpp)

target_link_libraries(BemaniMetadataParser PRIVATE Parser wxcore wxnet)