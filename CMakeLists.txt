cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

# Name the project
project(project1)
set(APPLICATION_LIBRARY GameLib)


# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Fetch spartanhero-resources from Github
include(FetchContent)
FetchContent_Declare(
        spartanhero-resources
        GIT_REPOSITORY https://github.com/charles-owen/spartanhero-resources.git
        GIT_TAG origin/main
)

FetchContent_MakeAvailable(spartanhero-resources)

file(COPY ${spartanhero-resources_SOURCE_DIR}/resources/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/stars/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)

# Fetch miniaudio from GitHub
include(FetchContent)
FetchContent_Declare(
        miniaudio
        GIT_REPOSITORY https://github.com/mackron/miniaudio.git
        GIT_TAG 0.11.21
)

FetchContent_MakeAvailable(miniaudio)

include_directories(${miniaudio_SOURCE_DIR})

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

set(SOURCE_FILES main.cpp
        pch.h
        GameApp.cpp
        GameApp.h
        ../../../../

)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

add_subdirectory(Tests)