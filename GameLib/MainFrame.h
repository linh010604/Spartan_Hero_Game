/**
 * @file MainFrame.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our city
    GameView *mGameView;
public:
    void Initialize();
};

#endif //PROJECT1_GAMELIB_MAINFRAME_H
