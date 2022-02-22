/**
 * @file AngleFish.cpp
 * @author Md Samad
 */

#include "pch.h"
#include "AngleFish.h"
#include "Aquarium.h"
#include <string>

using namespace std;

/// Fish filename
const wstring AngleFishImageName = L"images/angelfish.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
AngleFish::AngleFish(Aquarium* aquarium)
        :Fish(aquarium, AngleFishImageName)
{
    this->SetSpeedX(200);
    this->SetSpeedY(200);
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* AngleFish::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"angle fish");

    return itemNode;
}
