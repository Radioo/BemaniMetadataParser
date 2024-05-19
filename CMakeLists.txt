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

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

add_executable(BemaniMetadataParser main.cpp
        UI/App.cpp
        UI/App.hpp
        UI/Frames/BaseFrame.cpp
        UI/Frames/BaseFrame.hpp
        UI/Panels/HomePanel.cpp
        UI/Panels/HomePanel.hpp
        UI/Enums/MenuItem.hpp
        UI/Enums/Page.hpp
        UI/Panels/SDVX/SdvxParserPanel.cpp
        UI/Panels/SDVX/SdvxParserPanel.hpp
        UI/Panels/General/SeriesPanel.cpp
        UI/Panels/General/SeriesPanel.hpp
        UI/Panels/BasePanel.cpp
        UI/Panels/BasePanel.hpp)

add_custom_command(TARGET BemaniMetadataParser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/Parser/DB/DDL.sql
        ${CMAKE_CURRENT_BINARY_DIR}/DDL.sql)

target_link_libraries(BemaniMetadataParser PRIVATE Parser wxcore)