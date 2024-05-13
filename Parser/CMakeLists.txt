CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.1")

add_library(Parser STATIC
        Parser.cpp
        Parser.hpp
        DB/DbHelper.cpp
        DB/DbHelper.hpp)

target_link_libraries(Parser PRIVATE SQLiteCpp)

target_include_directories(Parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})