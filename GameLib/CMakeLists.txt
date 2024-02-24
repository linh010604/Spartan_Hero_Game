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
        ids.h
        Soundboard.cpp
        Soundboard.h

)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
