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
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h

)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
