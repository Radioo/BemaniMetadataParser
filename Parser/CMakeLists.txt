CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.1")

add_library(Parser STATIC
        Parser.cpp
        Parser.hpp
        DB/DbHelper.cpp
        DB/DbHelper.hpp
        Services/SeriesService.cpp
        Services/SeriesService.hpp
        Services/BaseService.cpp
        Services/BaseService.hpp
        Services/GameService.cpp
        Services/GameService.hpp
        Services/ReleaseService.cpp
        Services/ReleaseService.hpp
)

message(STATUS "PARSER_CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

target_link_libraries(Parser PRIVATE SQLiteCpp)

target_include_directories(Parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})