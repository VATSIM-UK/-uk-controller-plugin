#include "pch/pch.h"
#include "controller/ControllerPositionParser.h"

using UKControllerPlugin::Controller::ControllerPositionParser;

namespace UKControllerPluginTest {
    namespace Controller {

        TEST(ControllerPositionParser, NormaliseCallsignReplacesHyphensWithUnderscore)
        {
            ControllerPositionParser parser;
            std::string callsign = "LON-S-CTR";

            EXPECT_EQ(0, parser.NormaliseCallsign(callsign).compare("LON_S_CTR"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksForAirfields)
        {
            ControllerPositionParser parser;
            std::string callsign = "EGKK_APP";
            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("EGKK"));
        }

        TEST(ControllerPositionParser, ParseFacilityGracefullyHandlesNonCallsigns)
        {
            ControllerPositionParser parser;
            std::string callsign = "GATWICK";
            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("GATWICK"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksForEdgeCase)
        {
            ControllerPositionParser parser;
            std::string callsign = "ESSEX_APP";

            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("ESSEX"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksForLondonArea)
        {
            ControllerPositionParser parser;
            std::string callsign = "LON_S_CTR";

            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("LON"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksForLondonTerminal)
        {
            ControllerPositionParser parser;
            std::string callsign = "LTC_S_CTR";

            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("LTC"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksForScottishArea)
        {
            ControllerPositionParser parser;
            std::string callsign = "SCO_WD_CTR";

            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("SCO"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksForScottishTerminal)
        {
            ControllerPositionParser parser;
            std::string callsign = "STC_A_CTR";

            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("STC"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksForManchesterTerminal)
        {
            ControllerPositionParser parser;
            std::string callsign = "MAN_W_CTR";

            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("MAN"));
        }

        TEST(ControllerPositionParser, ParseFacilityFromCallsignWorksHyphenatedCallsigns)
        {
            ControllerPositionParser parser;
            std::string callsign = "LON-S_CTR";

            EXPECT_EQ(0, parser.ParseFacilityFromCallsign(callsign).compare("LON"));
        }

        TEST(ControllerPositionParser, IsMentoringPositionReturnsNonMentorIfNotTraining)
        {
            ControllerPositionParser parser;
            std::string callsign = "LON_CTR";

            EXPECT_EQ(parser.positionNotMentoring, parser.IsMentoringPosition(callsign));
        }

        TEST(ControllerPositionParser, IsMentoringPositionCanHandleHeathrow)
        {
            ControllerPositionParser parser;
            std::string callsign = "EGLL_N_APP";

            EXPECT_EQ(parser.positionNotMentoring, parser.IsMentoringPosition(callsign));
        }

        TEST(ControllerPositionParser, IsMentoringReturnsTraineeIfTraining)
        {
            ControllerPositionParser parser;
            std::string callsign = "EGGD_T_TWR";

            EXPECT_EQ(parser.positionTrainee, parser.IsMentoringPosition(callsign));
        }

        TEST(ControllerPositionParser, IsMentoringReturnsMentorIfMentoring)
        {
            ControllerPositionParser parser;
            std::string callsign = "EGGD_M_TWR";

            EXPECT_EQ(parser.positionMentor, parser.IsMentoringPosition(callsign));
        }
    }  // namespace Controller
}  // namespace UKControllerPluginTest
