cmake_minimum_required(VERSION 3.27)
project(GameLib)

set(CMAKE_CXX_STANDARD 17)

add_executable(project1 main.cpp
        Scoreboard.cpp
        Scoreboard.h
        Meter.cpp
        Meter.h)