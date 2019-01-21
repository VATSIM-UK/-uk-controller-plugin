#include "pch/pch.h"
#include "hold/HoldManager.h"
#include "mock/MockEuroscopePluginLoopbackInterface.h"
#include "mock/MockEuroScopeCFlightplanInterface.h"
#include "mock/MockEuroScopeCRadarTargetInterface.h"

using UKControllerPlugin::Hold::HoldManager;
using UKControllerPluginTest::Euroscope::MockEuroscopePluginLoopbackInterface;
using UKControllerPluginTest::Euroscope::MockEuroScopeCFlightPlanInterface;
using UKControllerPluginTest::Euroscope::MockEuroScopeCRadarTargetInterface;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::Test;

namespace UKControllerPluginTest {
    namespace Hold {

        class HoldManagerTest : public Test
        {
            public:
                HoldManagerTest(void)
                    : manager(mockPlugin)
                {
                    manager.AddHold("WILLO");

                    ON_CALL(mockFlightplan, GetCallsign())
                        .WillByDefault(Return("BAW123"));

                    ON_CALL(mockFlightplan, GetClearedAltitude())
                        .WillByDefault(Return(8000));

                    ON_CALL(mockRadarTarget, GetFlightLevel())
                        .WillByDefault(Return(9000));
                }

                NiceMock<MockEuroScopeCFlightPlanInterface> mockFlightplan;
                NiceMock<MockEuroScopeCRadarTargetInterface> mockRadarTarget;
                NiceMock<MockEuroscopePluginLoopbackInterface> mockPlugin;
                HoldManager manager;
        };

        TEST_F(HoldManagerTest, ItAddsAHold)
        {
            manager.AddHold("TIMBA");
            EXPECT_TRUE(manager.HasHold("TIMBA"));
        }

        TEST_F(HoldManagerTest, ItHandlesDuplicateHolds)
        {
            manager.AddHold("TIMBA");
            EXPECT_NO_THROW(manager.AddHold("TIMBA"));
        }

        TEST_F(HoldManagerTest, ItAddsAircraftToHold)
        {
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "WILLO");
            EXPECT_TRUE(manager.AircraftIsInHold("WILLO", "BAW123"));
        }

        TEST_F(HoldManagerTest, ItHandlesAddingAircraftToTheSameHold)
        {
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "WILLO");
            EXPECT_NO_THROW(manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "WILLO"));
        }

        TEST_F(HoldManagerTest, AddingAircraftToOneHoldRemovesFromAnother)
        {
            manager.AddHold("TIMBA");
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "WILLO");
            EXPECT_TRUE(manager.AircraftIsInHold("WILLO", "BAW123"));
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "TIMBA");
            EXPECT_FALSE(manager.AircraftIsInHold("WILLO", "BAW123"));
            EXPECT_TRUE(manager.AircraftIsInHold("TIMBA", "BAW123"));
        }

        TEST_F(HoldManagerTest, ItHandlesAddingToNonExistantHold)
        {
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "BIG");
            EXPECT_FALSE(manager.AircraftIsInHold("BIG", "BAW123"));
        }

        TEST_F(HoldManagerTest, ItRemovesAHold)
        {
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "WILLO");
            manager.RemoveHold("WILLO");
            EXPECT_FALSE(manager.HasHold("WILLO"));
            EXPECT_FALSE(manager.AircraftIsInHold("WILLO", "BAW123"));
        }

        TEST_F(HoldManagerTest, ItHandlesRemovingNonExistantHolds)
        {
            EXPECT_NO_THROW(manager.RemoveHold("BIG"));
        }

        TEST_F(HoldManagerTest, ItRemovesAnAircraftFromAnyHold)
        {
            manager.AddHold("BIG");
            manager.AddHold("LAM");
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "LAM");
            EXPECT_TRUE(manager.AircraftIsInHold("LAM", "BAW123"));
            manager.RemoveAircraftFromAnyHold("BAW123");
            EXPECT_FALSE(manager.AircraftIsInHold("LAM", "BAW123"));
        }

        TEST_F(HoldManagerTest, ItHandlesRemovingNonExistantAircraft)
        {
            manager.RemoveAircraftFromAnyHold("BAW123");
        }

        TEST_F(HoldManagerTest, ItReturnsAnEmptySetIfNoAircraftInHold)
        {
            EXPECT_EQ(0, manager.GetAircraftInHold("WILLO").size());
        }

        TEST_F(HoldManagerTest, ItReturnsAircraftInAHold)
        {
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "WILLO");
            EXPECT_EQ(1, manager.GetAircraftInHold("WILLO").count("BAW123"));
        }

        TEST_F(HoldManagerTest, AddingAircraftToAHoldSetsData)
        {
            manager.AddAircraftToHold(mockFlightplan, mockRadarTarget, "WILLO");
            auto hold = manager.GetAircraftInHold("WILLO");
            auto holdingData = hold.find("BAW123");

            EXPECT_TRUE(holdingData->callsign == "BAW123");
            EXPECT_TRUE(holdingData->holdIdentifier == "WILLO");
            EXPECT_EQ(8000, holdingData->clearedAltitude);
            EXPECT_EQ(9000, holdingData->reportedAltitude);
        }

    }  // namespace Hold
}  // namespace UKControllerPluginTest