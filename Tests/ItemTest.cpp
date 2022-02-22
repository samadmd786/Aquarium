/**
 * @file ItemTest.cpp
 * @author Md Samad
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Aquarium.h>

/// Fish filename
const std::wstring FishBetaImageName = L"images/beta.png";


/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Aquarium *aquarium) : Item(aquarium, FishBetaImageName) {}


};

TEST(ItemTest, Construct)
{
    Aquarium aquarium;
    ItemMock item(&aquarium);
}

TEST(ItemTest, GettersSetters)
{
    Aquarium aquarium;
    ItemMock item(&aquarium);

    // Test Initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);

    item.SetLocation(100, 200);

    // Center of the item should be a true
    ASSERT_TRUE(item.HitTest(100, 200));


    // Left of the item
    ASSERT_FALSE(item.HitTest(10, 200));

    // Right of the item
    ASSERT_FALSE(item.HitTest(200, 200));

    // Above the item
    ASSERT_FALSE(item.HitTest(100, 0));

    // Below the item
    ASSERT_FALSE(item.HitTest(100, 300));

    // On a item transparent pixel
    ASSERT_FALSE(item.HitTest(100-125/2+17, 200-117/2+16));



}