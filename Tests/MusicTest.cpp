/**
 * @file MusicTest.cpp
 * @author thaol
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Music.h>
#include <wx/sstream.h>

class MusicMock : public Music {
public:
    MusicMock(Game* game = nullptr) : Music(game) {}

};

class MusicTest : public ::testing::Test {
protected:
    void TestLoad(wxString xmlString, double expectedMeasure, double expectedBeat, wxString id) {
        Game game(nullptr);
        MusicMock music(&game);

        // Create an XML doc consisting of a single node
        wxXmlDocument doc;
        wxStringInputStream stream(xmlString);
        doc.Load(stream);

        //get node from document
        wxXmlNode* node = doc.GetRoot();

        //run XmlLoad
        music.XmlLoad(node);

        //Assertions
        ASSERT_EQ(music.GetMeasure(), expectedMeasure) << L"Incorrect measure of the note: ";
        ASSERT_EQ(music.GetBeat(), expectedBeat) << L"Incorrect beat of this note: ";
        ASSERT_EQ(music.GetId(), id) << L"Incorrect id loaded for this note: ";
    }
};


TEST_F(MusicTest, Construct){
    Game game(nullptr);
    MusicMock music(&game);
}

TEST_F(MusicTest, XmlLoad) {
    wxString xmlString1 = "<note id=\"t1\" sound=\"Eb4\" measure=\"1\" beat=\"4.25\" duration=\"0.25\"/>";
    wxString xmlString2 = "<note id=\"t4\" sound=\"G4\" measure=\"1\" beat=\"4.75\" duration=\"0.25\"/>";
    wxString xmlString3 = "<note id=\"t7\" sound=\"Ab4-long\" measure=\"7\" beat=\"1.0\" duration=\"1.0\"/>";;


    // Testing XmlLoad function with the different nodes
    TestLoad(xmlString1, 1, 4.25, L"t1");
    TestLoad(xmlString2, 1, 4.75, L"t4");
    TestLoad(xmlString3, 7, 1, L"t7");

}