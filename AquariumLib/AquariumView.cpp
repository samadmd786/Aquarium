/**
 * @file AquariumView.cpp
 * @author Md Samad
 */
#include "pch.h"
#include "AquariumView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include "FishBeta.h"
#include "Dory.h"
#include "AngleFish.h"
#include "Castle.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>

#endif

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{

    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddDoryFish, this, IDM_ADDFISHDORY);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishAngelFish, this, IDM_ADDFISHANGEL);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddCastle, this, IDMADDCASTLE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileOpen, this, wxID_OPEN);
    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &AquariumView::OnTimer, this);
    mStopWatch.Start();
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

}

/**
* Paint event, draws the window.
* @param event paint the object
*/
void AquariumView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    mAquarium.OnDraw(&dc);
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double) (newTime-mTime)*0.001;
    mTime = newTime;

    mAquarium.Update(elapsed);
}

/**
* Menu handler for Add Fish>Beta Fish
 * @param event Mouse event
*/
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = std::make_shared<FishBeta>(&mAquarium);
    fish->SetLocation(InitialX, InitialY);
    mAquarium.Add(fish);
    Refresh();
}

/**
* Menu handler for Add Fish>Dory Fish
* @param event Mouse event
*/
void AquariumView::OnAddDoryFish(wxCommandEvent& event)
{
    auto fish = std::make_shared<Dory>(&mAquarium);
    fish->SetLocation(InitialX, InitialY);
    mAquarium.Add(fish);
    Refresh();
}

/**
* Menu handler for Add Fish>Angle Fish
 * @param event Mouse event
*/
void AquariumView::OnAddFishAngelFish(wxCommandEvent& event)
{
    auto fish = std::make_shared<AngleFish>(&mAquarium);
    fish->SetLocation(InitialX, InitialY);
    mAquarium.Add(fish);
    Refresh();
}

/**
* Menu handler for Add Castle
 * @param event Mouse event
*/
void AquariumView::OnAddCastle(wxCommandEvent& event)
{
    auto castle = std::make_shared<Castle>(&mAquarium);
    castle->SetLocation(InitialX, InitialY);
    mAquarium.Add(castle);
    Refresh();
}

/**
 *  Handle the left mouse button down event
 *  @param event
 */
void AquariumView::OnLeftDown(wxMouseEvent& event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem!=nullptr) {
        // We have selected an item
        // Move it to the end of the list of items
        // you'll need code here to do that...
        mAquarium.PutItemToEnd(mGrabbedItem);
    }
}

/**
* Handle the left mouse button up event
 * @param event
*/
void AquariumView::OnLeftUp(wxMouseEvent& event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
 * @param event
*/
void AquariumView::OnMouseMove(wxMouseEvent& event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem!=nullptr) {
        // If an item is moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown()) {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else {
            // When the left button is released, we release the item
            mGrabbedItem = nullptr;
        }
        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Handle the File>Save As menu option
 * @param event The menu event
 */
void AquariumView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save Aquarium file"), "", "",
            "Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal()==wxID_CANCEL) {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mAquarium.Save(filename);
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, _("Load Aquarium file"), "", "",
            "Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
    if (loadFileDialog.ShowModal()==wxID_CANCEL) {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mAquarium.Load(filename);
    Refresh();
}

/**
 * update the aquarium at specific time
 * @param TimerEvent Time when to update the aquarium
 */
void AquariumView::OnTimer(wxTimerEvent& TimerEvent)
{
    Refresh();
}