/**
 * @file GameApp.h
 * @author Nicolas Roberts
 *
 * Main application class
 */

#ifndef PROJECT1_GAMEAPP_H
#define PROJECT1_GAMEAPP_H

#include "miniaudio.h"

/**
 * Main application class
 */
class GameApp : public wxApp {
private:
    /// The audio engine for miniaudio
    ma_engine mAudioEngine;
public:
    virtual bool OnInit();
    virtual int OnExit();

};


#endif //PROJECT1_GAMEAPP_H
