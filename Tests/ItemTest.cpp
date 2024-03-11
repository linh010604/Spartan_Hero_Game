/**
 * @file ItemTest.cpp
 * @author thaol
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Item.h>
#include <wx/sstream.h>

class ItemMock : public Item {
public:
    ItemMock(Game* game = nullptr) : Item(game) {}
    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    * */
    virtual void Accept(ItemVisitor* visitor) override { }
};

class ItemTest : public ::testing::Test {
protected:
    void TestLoad(wxString xmlString, int expectedItemsLocationX, int expectedItemsLocationY, wxString id) {
        Game game(nullptr);
        ItemMock item(&game);

        // Create an XML doc consisting of a single node
        wxXmlDocument doc;
        wxStringInputStream stream(xmlString);
        doc.Load(stream);

        //get node from document
        wxXmlNode* node = doc.GetRoot();

        //run XmlLoad
        item.XmlLoad(node);

        //Assertions
        ASSERT_EQ(item.GetX(), expectedItemsLocationX) << L"Incorrect x location for item: ";
        ASSERT_EQ(item.GetY(), expectedItemsLocationY) << L"Incorrect y location for item: ";
        ASSERT_EQ(item.GetId(), id) << L"Incorrect id loaded for item: ";
    }
};


TEST_F(ItemTest, Construct){
    Game game(nullptr);
   ItemMock item(&game);
}

TEST_F(ItemTest, XmlLoad) {
    wxString xmlString1 = "<image id=\"i600\" p=\"652,450\"/>";
    wxString xmlString2 = "<meter id=\"i921\" p=\"1027,362\" />";
    wxString xmlString3 = "<score-board id=\"i871\" p=\"1165,345\" />";;


    // Testing XmlLoad function with the different nodes
    TestLoad(xmlString1, 652, 450, L"i600");
    TestLoad(xmlString2, 1027, 362, L"i921");
    TestLoad(xmlString3, 1165, 345, L"i871");

}