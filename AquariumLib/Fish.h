/**
 * @file Fish.h
 * @author Md Samad
 *
 *
 */

#ifndef AQUARIUMAPP_CPP_FISH_H
#define AQUARIUMAPP_CPP_FISH_H

#include "Item.h"

/**
 * Base class for a fish
 * This applies to all the fish, but not the decor
 * items in the aquarium
 */
class Fish : public Item {

//protected:

private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;
public:
    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish&) = delete;

    /// Assignment operator
    void operator=(const Fish&) = delete;

    /**
     * Get the speed of fish in X direction
     * @return speed of fish in X direction
     */
    double GetSpeedX() { return mSpeedX; }

    /**
    * Get the speed of fish in Y direction
    * @return speed of fish in Y direction
    */
    double GetSpeedY() { return mSpeedY; }

    /**
     * Setter for speed in X direction
     * @param sx speed in X direction
     */
    void SetSpeedX(double sx)
    {
        mSpeedX = sx;
    }

    /**
    * Setter for speed in Y direction
    * @param sy speed in Y direction
    */
    void SetSpeedY(double sy)
    {
        mSpeedY = sy;
    }

    Fish(Aquarium* aquarium, const std::wstring& filename);

    void Update(double elapsed);

    wxXmlNode* XmlSave(wxXmlNode* node);

    void XmlLoad(wxXmlNode* node);
};

#endif //AQUARIUMAPP_CPP_FISH_H
