cmake_minimum_required(VERSION 3.28)
project(BemaniMetadataParser)

set(CMAKE_CXX_STANDARD 26)

add_executable(BemaniMetadataParser main.cpp
        Model/SDVX/SdvxSong.cpp
        Model/SDVX/SdvxSong.hpp
        Model/SDVX/SdvxChart.cpp
        Model/SDVX/SdvxChart.hpp
        Model/SDVX/SdvxSongEntry.cpp
        Model/SDVX/SdvxSongEntry.hpp
        Model/SDVX/SdvxChartEntry.cpp
        Model/SDVX/SdvxChartEntry.hpp
        Model/Game/Series.cpp
        Model/Game/Series.hpp
        Model/Game/Game.cpp
        Model/Game/Game.hpp
        Model/Game/GameRelease.cpp
        Model/Game/GameRelease.hpp)
