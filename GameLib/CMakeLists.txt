project(GameLib)

set(SOURCE_FILES pch.h
        Scoreboard.cpp
        Scoreboard.h
        Sound.cpp
        Sound.h
        Track.cpp
        Track.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        MainFrame.cpp
        MainFrame.h
        Item.cpp
        Item.h
        Puck.cpp
        Puck.h
        Level.cpp
        Level.h
        Key.cpp
        Key.h
        LevelLoader.cpp
        LevelLoader.h
        Soundboard.cpp
        Soundboard.h

)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
