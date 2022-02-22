/**
 * @file Aquarium.cpp
 * @author Md Samad
 */
#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "Dory.h"
#include "AngleFish.h"
#include "Castle.h"
#include <algorithm>

using namespace std;

/**
 * Draw the aquarium
 * @param dc The device contxt to draw on
 */
void Aquarium::OnDraw(wxDC* dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);
    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 64, 0));
    dc->DrawText(L"Under the Sea!", 10, 10);
    for (auto item: mItems) {
        item->Draw(dc);
    }

}

/**
 * Aquarium Constructor
 */
Aquarium::Aquarium()
{
    mBackground = make_unique<wxBitmap>(
            L"images/background1.png", wxBITMAP_TYPE_ANY);
    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());
}

/**
* Add an item to the aquarium
 * @param item New item to add
*/
void Aquarium::Add(shared_ptr<Item>(item))
{
    mItems.push_back(item);

}

/**
* Test an x,y click location to see if it clicked
 * on some item in the aquarium
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none
*/
std::shared_ptr<Item> Aquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i!=mItems.rend(); i++) {
        if ((*i)->HitTest(x, y)) {
            return *i;
        }

    }
    return nullptr;
}

/**
 *  Remove the fish from the vector, and it back to the end of that vector
 *  @param item fish that need to be moved
 */
void Aquarium::PutItemToEnd(std::shared_ptr<Item> item)
{
    auto loc = find(mItems.begin(), mItems.end(), item);
    if (loc!=mItems.end()) {
        mItems.erase(loc);
    }
    mItems.push_back(item);
}

/**
 * Save the aquarium as a .aqua XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * @param filename The filename of the file to save the aquarium to
 */
void Aquarium::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);

    // Iterate over all items and save them

    for (auto item: mItems) {
        item->XmlSave(root);
    }

    if (!xmlDoc.Save(filename, wxXML_NO_INDENTATION)) {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}

/**
* Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate
 *
 * @param filename The filename of the file to load the aquarium file
*/
void Aquarium::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename)) {
        wxMessageBox(L"Unable to load Aquarium file");
        return;
    }
    Clear();
    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // bodes of the document in memory!!!!
    //

    auto child = root->GetChildren();
    for (; child; child = child->GetNext()) {
        auto name = child->GetName();
        if (name==L"item") {
            XmlItem(child);
        }
    }
}

/**
* Clear the aquarium data.
 *
 * Deletes all known items in the aquarium
*/
void Aquarium::Clear()
{
    mItems.clear();
}

/**
 * Handle a node of any item.
 * @param node XML node
 */
void Aquarium::XmlItem(wxXmlNode* node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item
    auto type = node->GetAttribute(L"type");
    if (type==L"beta") {
        item = make_shared<FishBeta>(this);
    }
    if (type==L"dory") {
        item = make_shared<Dory>(this);
    }
    if (type==L"castle") {
        item = make_shared<Castle>(this);
    }
    if (type==L"angle fish") {
        item = make_shared<AngleFish>(this);
    }

    if (item!=nullptr) {
        item->XmlLoad(node);
        Add(item);
    }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Aquarium::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}