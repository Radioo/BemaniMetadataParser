CPMAddPackage("gh:vincentlaucsb/csv-parser#2.2.3")

add_library(ChartManager STATIC
        src/ChartManager.cpp
        src/Manager/GameManager.cpp
)

target_link_libraries(ChartManager PRIVATE csv)

target_include_directories(ChartManager PUBLIC include)