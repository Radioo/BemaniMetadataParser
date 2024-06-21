find_package(Iconv REQUIRED)

CPMAddPackage("gh:vincentlaucsb/csv-parser#2.2.3")
CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.1")
CPMAddPackage("gh:zeux/pugixml@1.14")

add_library(ChartManager STATIC
        src/ChartManager.cpp
        src/Manager/GameManager.cpp
        src/Manager/SDVXManager.cpp
        src/Util/DbUtil.cpp
        src/Util/EncodingUtil.cpp
        src/Util/FileUtil.cpp
)

target_link_libraries(ChartManager PRIVATE csv SQLiteCpp Iconv::Iconv pugixml gcov)

target_include_directories(ChartManager PUBLIC include)