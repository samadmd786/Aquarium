/**
 * @file Castle.h
 * @author Md Samad
 *
 *
 */

#ifndef AQUARIUMAPP_CPP_CASTLE_H
#define AQUARIUMAPP_CPP_CASTLE_H

#include "Aquarium.h"

/**
 * Class for a castle item
 */
class Castle : public Item {
private:

public:
    /// Default constructor (disabled)
    Castle() = delete;

    /// Copy constructor (disabled)
    Castle(const Castle&) = delete;

    /// Assignment operator
    void operator=(const Castle&) = delete;

    Castle(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node);
};

#endif //AQUARIUMAPP_CPP_CASTLE_H
