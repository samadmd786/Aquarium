/**
 * @file Castle.cpp
 * @author Md Samad
 */


#include "pch.h"
#include "Castle.h"
#include "Aquarium.h"
#include <string>

using namespace std;

/// Fish filename
const wstring CastleImageName = L"images/castle.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Castle::Castle(Aquarium* aquarium)
        :Item(aquarium, CastleImageName)
{

}
/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Castle::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"castle");

    return itemNode;
}