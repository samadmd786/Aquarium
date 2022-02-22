/**
 * @file Dory.h
 * @author Md Samad
 *
 *
 */

#ifndef AQUARIUMAPP_CPP_DORY_H
#define AQUARIUMAPP_CPP_DORY_H

#include "Fish.h"

/**
 * CLass to draw a Dory Fish in the aquarium
 */
class Dory : public Fish {
private:

public:
    /// Default constructor (disabled)
    Dory() = delete;

    /// Copy constructor (disabled)
    Dory(const Dory&) = delete;

    /// Assignment operator
    void operator=(const Dory&) = delete;

    Dory(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node);
};

#endif //AQUARIUMAPP_CPP_DORY_H
