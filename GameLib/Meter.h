/**
 * @file Meter.h
 * @author Nico Roberts
 */



#ifndef PROJECT1_METER_H
#define PROJECT1_METER_H


#include <string>
#include <wx/graphics.h> // Include the appropriate header for your graphics library

class Meter {
public:
    // Constructor
    Meter(const std::string& backgroundImagePath, const std::string& needleImagePath, const std::string& coverImagePath, const wxSize& size);

    // Draw the meter on the graphics context at position (x, y) with the score influencing the needle's rotation
    void Draw(wxGraphicsContext* graphics, int x, int y, double score);

private:
    // Bitmaps for the meter components
    wxBitmap background;
    wxBitmap needle;
    wxBitmap cover;

    // Size of the meter
    wxSize size;

    // Constants for the needle rotation and pivot
    static const double MaxNeedleRotation;   // Maximum rotation of the needle
    static const double NeedlePivotYOffset;  // Y-axis offset for the needle pivot
};



#endif //PROJECT1_METER_H
