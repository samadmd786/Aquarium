/**
 * @file AngleFish.h
 * @author Md Samad
 *
 *
 */

#ifndef AQUARIUMAPP_CPP_ANGLEFISH_H
#define AQUARIUMAPP_CPP_ANGLEFISH_H

#include "Fish.h"

/**
 * Class to draw an Angel Fish in the aquarium
 */
class AngleFish : public Fish {
private:

public:
    /// Default constructor (disabled)
    AngleFish() = delete;

    /// Copy constructor (disabled)
    AngleFish(const AngleFish&) = delete;

    /// Assignment operator
    void operator=(const AngleFish&) = delete;

    AngleFish(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node);

//    void Update(double elapsed);
};

#endif //AQUARIUMAPP_CPP_ANGLEFISH_H
