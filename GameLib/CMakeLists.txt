project(GameLib)

set(SOURCE_FILES pch.h
        ItemScoreboard.cpp
        ItemScoreboard.h
        Sound.cpp
        Sound.h
        ItemKey.cpp
        ItemKey.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        MainFrame.cpp
        MainFrame.h
        Item.cpp
        Item.h
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
        DeclarationNote.cpp
        DeclarationNote.h
        VisitorSoundboard.cpp
        VisitorSoundboard.h
        VisitorMeter.cpp
        VisitorMeter.h
        GameStateManager.cpp
        GameStateManager.h

)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
