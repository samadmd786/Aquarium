/**
 * @file Fish.cpp
 * @author Md Samad
 */

#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"
#include <string>
#include <memory>

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedY = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedY = 20;

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium* aquarium, const std::wstring& filename)
        :Item(aquarium, filename)
{
    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    std::uniform_real_distribution<> distributionY(MinSpeedY, MaxSpeedY);
    mSpeedX = distribution(aquarium->GetRandom());
    mSpeedY = distributionY(aquarium->GetRandom());
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    SetLocation(GetX()+mSpeedX*elapsed,
            GetY()+mSpeedY*elapsed);

    if (mSpeedX>0 && GetX()>=(GetAquarium()->GetWidth()-10-(GetItemWidth()/2))) {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }
    else if (mSpeedX<0 && GetX()<=(10+(GetItemWidth()/2))) {
        mSpeedX = -mSpeedX;
        SetMirror(false);
    }
    else if (mSpeedY>0 && GetY()>=(GetAquarium()->GetHeight()-10-(GetItemHeight()/2))) {
        mSpeedY = -mSpeedY;

    }
    else if (mSpeedY<0 && GetY()<=(10+(GetItemHeight()/2))) {
        mSpeedY = -mSpeedY;
    }

}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Fish::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"xSpeed", wxString::FromDouble(GetSpeedX()));
    itemNode->AddAttribute(L"ySpeed", wxString::FromDouble(GetSpeedY()));

    return itemNode;
}

/**
* Load the attribute for an item node.
*
* This is the base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* @param node The Xml node we are loading the item from
*/
void Fish::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    node->GetAttribute(L"xSpeed", L"0").ToDouble(&mSpeedX);
    node->GetAttribute(L"ySpeed", L"0").ToDouble(&mSpeedY);
}
