cmake_minimum_required(VERSION 3.27)
project(project1)
set(APPLICATION_LIBRARY GameLib)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

set(SOURCE_FILES main.cpp
        pch.h
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})
#temp comment