project(GameLib)

set(SOURCE_FILES pch.h
        Scoreboard.cpp
        Scoreboard.h
        Meter.cpp
        Meter.h
        Sound.cpp
        Sound.h
        Track.cpp
        Track.h
        Item.cpp
        Item.h

)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
