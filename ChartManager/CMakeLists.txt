CPMAddPackage("gh:vincentlaucsb/csv-parser#2.2.3")
CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.1")

add_library(ChartManager STATIC
        src/ChartManager.cpp
        src/Manager/GameManager.cpp
        src/Util/DbUtil.cpp
)

target_link_libraries(ChartManager PRIVATE csv SQLiteCpp)

target_include_directories(ChartManager PUBLIC include)