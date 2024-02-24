/**
 * @file Meter.cpp
 * @author Nico Roberts
 */
#include "pch.h"
#include "Meter.h"

// Definitions for the static constants
const double Meter::MaxNeedleRotation = 0.9;
const double Meter::NeedlePivotYOffset = 0.80;

// Constructor implementation
Meter::Meter(const std::string& backgroundImagePath, const std::string& needleImagePath, const std::string& coverImagePath, const wxSize& size)
    : background(wxBitmap(backgroundImagePath, wxBITMAP_TYPE_ANY)),
      needle(wxBitmap(needleImagePath, wxBITMAP_TYPE_ANY)),
      cover(wxBitmap(coverImagePath, wxBITMAP_TYPE_ANY)),
      size(size)
{
    // Constructor body (if needed)
}

// Draw method implementation
void Meter::Draw(wxGraphicsContext* graphics, int x, int y, double score) {
    // First, draw the background
    graphics->DrawBitmap(background, x - size.GetWidth()/2, y - size.GetHeight()/2, size.GetWidth(), size.GetHeight());

    // Calculate needle rotation based on score
    double needleRotation = (score * 2 - 1) * MaxNeedleRotation;

    // Calculate the pivot point for the needle
    int wid = size.GetWidth();
    int hit = size.GetHeight();
    int needlePivotY = static_cast<int>(hit * NeedlePivotYOffset);

    // Save the current state of graphics
    graphics->PushState();

    // Translate and rotate the graphics context to draw the needle
    graphics->Translate(x, y + needlePivotY - hit / 2);
    graphics->Rotate(needleRotation);
    graphics->DrawBitmap(needle, -wid / 2, -needlePivotY, wid, hit);

    // Restore the graphics state
    graphics->PopState();

    // Lastly, draw the cover
    graphics->DrawBitmap(cover, x - size.GetWidth()/2, y - size.GetHeight()/2, size.GetWidth(), size.GetHeight());
}
