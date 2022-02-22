/**
 * @file Item.h
 * @author Md Samad
*/
#ifndef AQUARIUM_ITEM_H
#define AQUARIUM_ITEM_H

#include <wx/xml/xml.h>

class Aquarium;

/**
 * Base class for items in the aquarium
 */
class Item {
private:
    /// The aquarium this item is contained in
    Aquarium* mAquarium;

    bool mMirror = false; ///< True mirrors the ite image

    // Item location in the aquarium
    double mX = 0;     ///< X location for the center of the item
    double mY = 0;     ///< Y location for the center of the item
    /// The underlying fish image

    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

protected:
    Item(Aquarium* aquarium, const std::wstring& filename);

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item&) = delete;

    ~Item();

    /**
     * The X location of the item
     * @returns X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @returns Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Get the width of the item
     * @return Width of the item in pixel
     */
    double GetItemWidth() const { return mItemImage->GetWidth(); }

    /**
     * Get the height of the item
     * @return Height of the item in pixel
     */
    double GetItemHeight() const { return mItemImage->GetHeight(); }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y)
    {
        mX = x;
        mY = y;
    }

    void Draw(wxDC* dc);

    bool HitTest(int x, int y);

    /**
     * Get the pointer to the Aquarium object
     * @return Pointer to Aquarium object
     */
    Aquarium* GetAquarium() { return mAquarium; }

    virtual wxXmlNode* XmlSave(wxXmlNode* node);

    void XmlLoad(wxXmlNode* node);

    /**
     * Handle updates for animation
    * @param elapsed The time since the last update
    */
    virtual void Update(double elapsed) { }

    void SetMirror(bool m);
};

#endif //AQUARIUM_ITEM_H