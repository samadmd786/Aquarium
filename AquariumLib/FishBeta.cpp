/**
 * @file FishBeta.cpp
 * @author Md Samad
 */

#include "pch.h"
#include "FishBeta.h"
#include "Aquarium.h"
#include <string>

using namespace std;

/// Fish filename
const wstring FishBetaImageName = L"images/beta.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBeta::FishBeta(Aquarium* aquarium)
        :Fish(aquarium, FishBetaImageName)
{
    this->SetSpeedX(100);
    this->SetSpeedY(100);

}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"beta");

    return itemNode;
}
