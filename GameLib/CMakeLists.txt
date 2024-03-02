project(GameLib)

set(SOURCE_FILES pch.h
        ItemScoreboard.cpp
        ItemScoreboard.h
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
        ItemSoundboard.cpp
        ItemSoundboard.h
        ItemMeter.cpp
        ItemMeter.h
        Declaration.cpp
        Declaration.h
        DeclarationImage.cpp
        DeclarationImage.h
        ItemImage.cpp
        ItemImage.h
        DeclarationMeter.cpp
        DeclarationMeter.h
        DeclarationScoreBoard.cpp
        DeclarationScoreBoard.h
        DeclarationSoundBoard.cpp
        DeclarationSoundBoard.h

)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
