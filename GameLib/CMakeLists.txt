project(GameLib)

set(SOURCE_FILES pch.h
        Scoreboard.cpp
        Scoreboard.h
        Meter.cpp
        Meter.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
