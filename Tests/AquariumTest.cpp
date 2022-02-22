/**
 * @file AquariumTest.cpp
 * @author Md Samad
 */

#include <pch.h>
#include <wx/filename.h>
#include "gtest/gtest.h"
#include <Aquarium.h>
#include <FishBeta.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <Dory.h>
#include <AngleFish.h>
#include <Castle.h>

using namespace std;

const unsigned int RandomSeed = 1238197374;

class AquariumTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir()+L"/aquarium";
        if (!wxFileName::DirExists(path)) {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString& filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;
        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
    }

    /**
     * Populate an aquarium with three beta fish
     */
    void PopulateThreeBetas(Aquarium* aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);
        auto fish1 = make_shared<FishBeta>(aquarium);
        fish1->SetLocation(100, 200);

        aquarium->Add(fish1);

        auto fish2 = make_shared<FishBeta>(aquarium);
        fish2->SetLocation(400, 400);
        aquarium->Add(fish2);

        auto fish3 = make_shared<FishBeta>(aquarium);
        fish3->SetLocation(600, 100);
        aquarium->Add(fish3);

    }

    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the potions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

        ASSERT_TRUE(regex_search(xml,
                wregex(L"<item x=\"100\" y=\"200\" xSpeed=\"100\" ySpeed=\"100\"")));
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<item x=\"100\" y=\"200\" xSpeed=\"100\" ySpeed=\"100\"")));
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<item x=\"100\" y=\"200\" xSpeed=\"100\" ySpeed=\"100\"")));
        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
    }

    /**
     * Populate an aquarium with all types of items
     */
    void PopulateAllTypes(Aquarium* aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);
        auto drawDoryFish = make_shared<Dory>(aquarium);
        drawDoryFish->SetLocation(200, 200);
        aquarium->Add(drawDoryFish);

        auto drawAngelFish = make_shared<AngleFish>(aquarium);
        drawAngelFish->SetLocation(300, 400);
        aquarium->Add(drawAngelFish);

        auto drawCastle = make_shared<Castle>(aquarium);
        drawCastle->SetLocation(400, 100);
        aquarium->Add(drawCastle);
    }

    void TestAllTypes(wxString filename)
    {

        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the potions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"200\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"300\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"100\"")));

        ASSERT_TRUE(regex_search(xml,
                wregex(L"<item x=\"200\" y=\"200\" xSpeed=\"50\" ySpeed=\"50\"")));
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<item x=\"300\" y=\"400\" xSpeed=\"200\" ySpeed=\"200\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"dory\"/><item.* type=\"angle fish\"/><item.* type=\"castle\"/></aqua>")));


    }
};

TEST_F(AquariumTest, Construct)
{
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
                                                   L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    fish1->SetLocation(100, 200);
    aquarium.Add(fish1);

    ASSERT_TRUE(aquarium.HitTest(100, 200)==fish1) <<
                                                   L"Testing fish at 100, 200";
    fish2->SetLocation(100, 200);
    aquarium.Add(fish2);

    ASSERT_TRUE(aquarium.HitTest(100, 200)==fish2) << L"Testing overlapping";

}

TEST_F(AquariumTest, Save)
{
    // Create a path to temporary files
    auto path = TempPath();

    //Create an aquarium
    Aquarium aquarium;
    aquarium.GetRandom().seed(RandomSeed);

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path+L"/test.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    //
    // Now Populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path+L"test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    aquarium3.GetRandom().seed(RandomSeed);
    PopulateAllTypes(&aquarium3);

    auto file3 = path+L"test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);


}

TEST_F(AquariumTest, Clear)
{
    Aquarium aquarium;
    auto path = TempPath();
    auto file4 = path+L"/test.aqua";
    PopulateThreeBetas(&aquarium);
    aquarium.Clear();
    aquarium.Save(file4);
    TestEmpty(file4);
}

TEST_F(AquariumTest, Load)
{
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;
    Aquarium aquarium2;
    aquarium2.GetRandom().seed(RandomSeed);

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path+L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    aquarium2.Load(file1);
    aquarium2.Save(file1);
    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);
    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);
    TestAllTypes(file3);

    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    aquarium3.Load(file3);
    aquarium3.Save(file3);
    TestAllTypes(file3);
}
