/**
 * @file ItemVisitor.cpp
 * @author thaol
 */

#include "pch.h"


#include "ItemVisitor.h"
#include "ItemMeter.h"
#include <iostream>

void ItemVisitor::VisitItemMeter(ItemMeter* meter)
{
    double hitNotes = CalculateHitNotes();
    meter->UpdateMeter(hitNotesRatio);
}