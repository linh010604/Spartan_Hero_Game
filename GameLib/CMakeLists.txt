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
        ItemSoundBoardVisitor.cpp
        ItemSoundBoardVisitor.h
        Music.cpp
        Music.h
        GameStateManager.cpp
        GameStateManager.h
        ItemVisitor.cpp
        ItemVisitor.h
        DeclarationVisitor.cpp
        DeclarationVisitor.h
        DeclarationNoteVisitor.cpp
        DeclarationNoteVisitor.h
        LevelLoader.cpp
        LevelLoader.h


)

set(wxBUILD_PRECOMP OFF)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)