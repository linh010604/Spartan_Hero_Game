/**
 * @file ids.h
 * @author thaol
 *
 * File containing all ids
 */

#ifndef PROJECT1_GAMELIB_IDS_H
#define PROJECT1_GAMELIB_IDS_H

#include <wx/wxprec.h>

/**
 * Menu id values
 */
enum IDs {
    /// Level>Level 0 menu option
    IDM_LEVEL0 = wxID_HIGHEST + 1,

    /// Level>Level 1 Report menu option
    IDM_LEVEL1,

    /// Level>Level 2 Report menu option
    IDM_LEVEL2,

    /// Level>Level 3 Report menu option
    IDM_LEVEL3,

    /// Level>Autoplay Report menu option
    IDM_AUTOPLAY,
};

#endif //PROJECT1_GAMELIB_IDS_H
