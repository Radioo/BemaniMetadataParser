cmake_minimum_required(VERSION 3.22)
project(BemaniMetadataParser)

set(CMAKE_CXX_STANDARD 20)
set(wxBUILD_SHARED OFF)

if(${MSVC})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:WinMainCRTStartup")
endif()

include(cmake/get_cpm.cmake)

add_subdirectory(ChartManager)

CPMAddPackage(
        NAME wxWidgets
        VERSION 3.2.5
        GITHUB_REPOSITORY wxWidgets/wxWidgets
        OPTIONS
            "wxUSE_STL yes"
)

add_executable(BemaniMetadataParser
        main.cpp
        src/App.cpp
        src/Helpers/UiHelper.cpp
        src/Frames/MainFrame.cpp
        src/Panels/SeriesPanel.cpp
        src/Panels/EditSeriesPanel.cpp
        src/Panels/GamePanel.cpp
        src/Panels/EditGamePanel.cpp
        src/Panels/ReleasePanel.cpp
        src/Panels/EditReleasePanel.cpp
        src/Panels/ReleasePickerPanel.cpp
        src/Panels/SdvxParserMenuPanel.cpp
        src/Panels/SdvxParserPanel.cpp
)

# Include msw/rc for windows
message(STATUS "wxWidgets_INCLUDE_DIRS: ${wxWidgets_SOURCE_DIR}")
target_sources(BemaniMetadataParser PRIVATE ${wxWidgets_SOURCE_DIR}/include/wx/msw/wx.rc)

target_link_libraries(BemaniMetadataParser PRIVATE ChartManager wxcore)