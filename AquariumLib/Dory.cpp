/**
 * @file Dory.cpp
 * @author Md Samad
 */

#include "pch.h"
#include "Dory.h"
#include "Aquarium.h"
#include <string>

using namespace std;

/// Fish filename
const wstring DoryImageName = L"images/dory.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Dory::Dory(Aquarium* aquarium)
        :Fish(aquarium, DoryImageName)
{
    this->SetSpeedX(50);
    this->SetSpeedY(50);
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Dory::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"dory");

    return itemNode;
}


