#include "pch/pch.h"
#include "oceanic/OceanicEventHandler.h"
#include "mock/MockCurlApi.h"
#include "mock/MockTaskRunnerInterface.h"
#include "curl/CurlRequest.h"
#include "curl/CurlResponse.h"
#include "mock/MockEuroScopeCFlightplanInterface.h"
#include "mock/MockEuroScopeCRadarTargetInterface.h"
#include "tag/TagData.h"
#include "dialog/DialogManager.h"
#include "dialog/DialogData.h"
#include "mock/MockDialogProvider.h"

using ::testing::Test;
using testing::NiceMock;
using testing::Return;
using testing::_;
using UKControllerPlugin::Oceanic::OceanicEventHandler;
using UKControllerPlugin::Oceanic::Clearance;
using UKControllerPlugin::Curl::CurlRequest;
using UKControllerPlugin::Curl::CurlResponse;
using UKControllerPlugin::Tag::TagData;
using UKControllerPluginTest::Euroscope::MockEuroScopeCFlightPlanInterface;
using UKControllerPluginTest::Euroscope::MockEuroScopeCRadarTargetInterface;
using UKControllerPlugin::Dialog::DialogManager;
using UKControllerPlugin::Dialog::DialogData;
using UKControllerPluginTest::Dialog::MockDialogProvider;

namespace UKControllerPluginTest {
    namespace Oceanic {

        class OceanicEventHandlerTest : public Test
        {
            public:
                OceanicEventHandlerTest()
                    : dialog(dialogProvider), handler(mockCurl, mockTaskRunner, dialog)
                {
                    dialog.AddDialog(this->dialogData);

                    ON_CALL(this->flightplan, GetCallsign())
                        .WillByDefault(Return("BAW123"));
                }

                void SimulateNattrakCall(bool curlError, uint64_t statusCode, std::string body)
                {
                    CurlRequest expectedRequest(
                        "https://nattrak.vatsim.net/pluginapi.php",
                        CurlRequest::METHOD_GET
                    );
                    EXPECT_CALL(mockCurl, MakeCurlRequest(expectedRequest))
                        .Times(1)
                        .WillOnce(Return(CurlResponse(body, curlError, statusCode)));

                    this->handler.TimedEventTrigger();
                }


                TagData GetTagData()
                {
                    return TagData(
                        flightplan,
                        radarTarget,
                        118,
                        EuroScopePlugIn::TAG_DATA_CORRELATED,
                        itemString,
                        &euroscopeColourCode,
                        &tagColour,
                        &fontSize
                    );
                }

                DialogData dialogData = {IDD_OCEANIC_CLEARANCE, "Test"};
                NiceMock<MockDialogProvider> dialogProvider;
                DialogManager dialog;
                double fontSize = 24.1;
                COLORREF tagColour = RGB(255, 255, 255);
                int euroscopeColourCode = EuroScopePlugIn::TAG_COLOR_ASSUMED;
                char itemString[16] = "Foooooo";
                NiceMock<MockEuroScopeCFlightPlanInterface> flightplan;
                NiceMock<MockEuroScopeCRadarTargetInterface> radarTarget;
                NiceMock<Curl::MockCurlApi> mockCurl;
                TaskManager::MockTaskRunnerInterface mockTaskRunner;
                OceanicEventHandler handler;
        };

        TEST_F(OceanicEventHandlerTest, ItHandlesCurlErrorsFromNattrak)
        {
            this->SimulateNattrakCall(true, 0L, "");
            EXPECT_EQ(0, this->handler.CountClearances());
        }

        TEST_F(OceanicEventHandlerTest, ItHandlesNonOkResponsesFromNattrak)
        {
            this->SimulateNattrakCall(false, 404, "");
            EXPECT_EQ(0, this->handler.CountClearances());
        }

        TEST_F(OceanicEventHandlerTest, ItHandlesInvalidJsonFromNattrak)
        {
            this->SimulateNattrakCall(false, 200, "{]");
            EXPECT_EQ(0, this->handler.CountClearances());
        }

        TEST_F(OceanicEventHandlerTest, ItHandlesNonArrayDataFromNattrak)
        {
            this->SimulateNattrakCall(false, 200, nlohmann::json::object().dump());
            EXPECT_EQ(0, this->handler.CountClearances());
        }

        TEST_F(OceanicEventHandlerTest, ItHandlesInvalidClearancesFromNattrak)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", 123}, // Bad status
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceData}).dump());
            EXPECT_EQ(0, this->handler.CountClearances());
            EXPECT_EQ(this->handler.invalidClearance, this->handler.GetClearanceForCallsign("BAW123"));
        }

        TEST_F(OceanicEventHandlerTest, ItUpdatesClearanceDataFromNattrak)
        {
            nlohmann::json clearanceOne = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            nlohmann::json clearanceTwo = {
                {"callsign", "BAW456"},
                {"status", "PENDING"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", nlohmann::json::value_t::null},
                {"extra_info", nlohmann::json::value_t::null},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceOne, clearanceTwo}).dump());
            EXPECT_EQ(2, this->handler.CountClearances());

            const Clearance& nattrakClearanceOne = this->handler.GetClearanceForCallsign("BAW123");
            EXPECT_EQ("BAW123", nattrakClearanceOne.callsign);
            EXPECT_EQ("CLEARED", nattrakClearanceOne.status);
            EXPECT_EQ("A", nattrakClearanceOne.track);
            EXPECT_EQ("MALOT", nattrakClearanceOne.entryFix);
            EXPECT_EQ("320", nattrakClearanceOne.flightLevel);
            EXPECT_EQ(".85", nattrakClearanceOne.mach);
            EXPECT_EQ("01:25", nattrakClearanceOne.entryTime);
            EXPECT_EQ("2021-03-28 11:12:34", nattrakClearanceOne.clearanceIssued);
            EXPECT_EQ("More info", nattrakClearanceOne.extra);


            const Clearance& nattrakClearanceTwo = this->handler.GetClearanceForCallsign("BAW456");
            EXPECT_EQ("BAW456", nattrakClearanceTwo.callsign);
            EXPECT_EQ("PENDING", nattrakClearanceTwo.status);
            EXPECT_EQ("A", nattrakClearanceTwo.track);
            EXPECT_EQ("MALOT", nattrakClearanceTwo.entryFix);
            EXPECT_EQ("320", nattrakClearanceTwo.flightLevel);
            EXPECT_EQ(".85", nattrakClearanceTwo.mach);
            EXPECT_EQ("01:25", nattrakClearanceTwo.entryTime);
            EXPECT_EQ("", nattrakClearanceTwo.clearanceIssued);
            EXPECT_EQ("", nattrakClearanceTwo.extra);
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsTrueWithAllFilledIn)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_TRUE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsTrueWithNulls)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "PENDING"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", nlohmann::json::value_t::null},
                {"extra_info", nlohmann::json::value_t::null},
            };

            EXPECT_TRUE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingCallsign)
        {
            nlohmann::json clearanceData = {
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseCallsignNotString)
        {
            nlohmann::json clearanceData = {
                {"callsign", 123},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingStatus)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseStatusNotString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", 123},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }


        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingNat)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseNatNotString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", 123},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingFix)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseFixNotString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", 123},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingLevel)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseLevelNotString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", 123},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseLevelNotValid)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "123abc"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingMach)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMachNotString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", 123},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingEstimatingTime)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseEstimatingTimeNotString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", 123},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingClearanceIssued)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseClearanceIssuedNotNullOrString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", 123},
                {"extra_info", "More info"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseMissingExtraInfo)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ClearanceValidReturnsFalseExtraInfoNotNullOrString)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", 123},
            };

            EXPECT_FALSE(this->handler.NattrakClearanceValid(clearanceData));
        }

        TEST_F(OceanicEventHandlerTest, ItHasTheClearanceIndicatorTagItem)
        {
            EXPECT_EQ("Nattrak Oceanic Clearance Indicator", this->handler.GetTagItemDescription(118));
        }

        TEST_F(OceanicEventHandlerTest, TagItemIsUnsetForNoNattrakData)
        {
            TagData data = this->GetTagData();
            this->handler.SetTagItemData(data);
            EXPECT_EQ("Foooooo", data.GetItemString());
            EXPECT_EQ(RGB(255, 255, 255), data.GetTagColour());
        }

        TEST_F(OceanicEventHandlerTest, TagItemIsSetForPendingClearance)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "PENDING"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceData}).dump());


            TagData data = this->GetTagData();
            this->handler.SetTagItemData(data);
            EXPECT_EQ("OCA", data.GetItemString());
            EXPECT_EQ(this->handler.clearanceIndicatorPending, data.GetTagColour());
        }

        TEST_F(OceanicEventHandlerTest, TagItemIsSetForClearedWhenClearedLevelIsEqualToCurrentControllerAssignedLevel)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceData}).dump());

            ON_CALL(this->flightplan, GetClearedAltitude())
                .WillByDefault(Return(32000));

            ON_CALL(this->flightplan, GetCruiseLevel())
                .WillByDefault(Return(35000));

            TagData data = this->GetTagData();
            this->handler.SetTagItemData(data);
            EXPECT_EQ("OCA", data.GetItemString());
            EXPECT_EQ(this->handler.clearanceIndicatorOk, data.GetTagColour());
        }

        TEST_F(OceanicEventHandlerTest, TagItemIsSetForClearedWhenClearedLevelIsEqualToRequestedFlightLevel)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceData}).dump());

            ON_CALL(this->flightplan, GetClearedAltitude())
                .WillByDefault(Return(0));

            ON_CALL(this->flightplan, GetCruiseLevel())
                .WillByDefault(Return(32000));

            TagData data = this->GetTagData();
            this->handler.SetTagItemData(data);
            EXPECT_EQ("OCA", data.GetItemString());
            EXPECT_EQ(this->handler.clearanceIndicatorOk, data.GetTagColour());
        }

        TEST_F(OceanicEventHandlerTest, TagItemIsSetForActionRequiredWhenClearedLevelIsDifferentToControllerAssigned)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceData}).dump());

            ON_CALL(this->flightplan, GetClearedAltitude())
                .WillByDefault(Return(31000));

            ON_CALL(this->flightplan, GetCruiseLevel())
                .WillByDefault(Return(32000));

            TagData data = this->GetTagData();
            this->handler.SetTagItemData(data);
            EXPECT_EQ("OCA", data.GetItemString());
            EXPECT_EQ(this->handler.clearanceIndicatorActionRequired, data.GetTagColour());
        }

        TEST_F(OceanicEventHandlerTest, TagItemIsSetForActionRequiredWhenClearedLevelIsDifferentToRequested)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceData}).dump());

            ON_CALL(this->flightplan, GetClearedAltitude())
                .WillByDefault(Return(0));

            ON_CALL(this->flightplan, GetCruiseLevel())
                .WillByDefault(Return(31000));

            TagData data = this->GetTagData();
            this->handler.SetTagItemData(data);
            EXPECT_EQ("OCA", data.GetItemString());
            EXPECT_EQ(this->handler.clearanceIndicatorActionRequired, data.GetTagColour());
        }

        TEST_F(OceanicEventHandlerTest, TestItOpensDialogWithValidClearance)
        {
            nlohmann::json clearanceData = {
                {"callsign", "BAW123"},
                {"status", "CLEARED"},
                {"nat", "A"},
                {"fix", "MALOT"},
                {"level", "320"},
                {"mach", ".85"},
                {"estimating_time", "01:25"},
                {"clearance_issued", "2021-03-28 11:12:34"},
                {"extra_info", "More info"},
            };

            this->SimulateNattrakCall(false, 200, nlohmann::json::array({clearanceData}).dump());

            EXPECT_CALL(this->dialogProvider, OpenDialog(this->dialogData, _))
                .Times(1);

            this->handler.TagFunction(this->flightplan, NiceMock<MockEuroScopeCRadarTargetInterface>(), "", {});
        }

        TEST_F(OceanicEventHandlerTest, TestItOpensDialogWithNoValidClearance)
        {
            EXPECT_CALL(this->dialogProvider, OpenDialog(this->dialogData, _))
                .Times(1);

            this->handler.TagFunction(this->flightplan, NiceMock<MockEuroScopeCRadarTargetInterface>(), "", {});
        }
    }  // namespace Oceanic
}  // namespace UKControllerPluginTest
