/**
 * @file AquariumView.h
 * @author Md Samad
 *
 *
 */

#ifndef AQUARIUM_AQUARIUMVIEW_H
#define AQUARIUM_AQUARIUMVIEW_H

#include "Aquarium.h"

/**
 * Aquarium class
 */
class AquariumView : public wxWindow {
private:

    void OnPaint(wxPaintEvent& event);

    /// An object  that describes our aquarium
    Aquarium mAquarium;

    /// Any item we are currently dragging
    std::shared_ptr<Item> mGrabbedItem;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

public:
    void Initialize(wxFrame* parent);

    void OnAddFishBetaFish(wxCommandEvent& event);

    void OnLeftDown(wxMouseEvent& event);

    void OnLeftUp(wxMouseEvent& event);

    void OnMouseMove(wxMouseEvent& event);

    void OnAddDoryFish(wxCommandEvent& event);

    void OnAddFishAngelFish(wxCommandEvent& event);

    void OnAddCastle(wxCommandEvent& event);

    void OnFileSaveAs(wxCommandEvent& event);

    void OnFileOpen(wxCommandEvent& event);

    void OnTimer(wxTimerEvent& event);
};

#endif //AQUARIUM_AQUARIUMVIEW_H
