cmake_minimum_required(VERSION 3.22)
project(BemaniMetadataParser)

set(CMAKE_CXX_STANDARD 20)
set(wxBUILD_SHARED OFF)

if(${MSVC})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:WinMainCRTStartup")
endif()

include(cmake/get_cpm.cmake)

add_subdirectory(ChartManager)

CPMAddPackage("gh:wxWidgets/wxWidgets@3.2.5")

add_executable(BemaniMetadataParser
        main.cpp
        src/App.cpp
)

target_link_libraries(BemaniMetadataParser PRIVATE ChartManager wxcore)