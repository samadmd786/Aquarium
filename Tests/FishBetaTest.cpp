/**
 * @file TestFishBeta.cpp
 * @author Md Samad
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Aquarium.h>
#include <FishBeta.h>

using namespace std;

TEST(FishBetaTest, Construct)
{
    Aquarium aquarium;
    FishBeta fish(&aquarium);

    // Give it a location
    // Always make the numbers different, in case they are mixed up

}
