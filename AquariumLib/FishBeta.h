/**
 * @file FishBeta.h
 * @author Md Samad
 *
 *
 */

#ifndef AQUARIUM_FISHBETA_H
#define AQUARIUM_FISHBETA_H

#include <wx/xml/xml.h>
#include "Fish.h"

/**
 * A class to make a Beta Fish
 */
class FishBeta : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta&) = delete;

    /// Assignment operator
    void operator=(const FishBeta&) = delete;

    FishBeta(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

//    void Update(double elapsed) override;
};

#endif //AQUARIUM_FISHBETA_H