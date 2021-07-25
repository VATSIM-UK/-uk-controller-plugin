#include "pch/pch.h"
#include "intention/IntentionCodeCache.h"
#include "intention/IntentionCodeData.h"
#include "mock/MockEuroscopeExtractedRouteInterface.h"

using UKControllerPlugin::IntentionCode::IntentionCodeCache;
using UKControllerPlugin::IntentionCode::IntentionCodeData;
using UKControllerPluginTest::Euroscope::MockEuroscopeExtractedRouteInterface;
using ::testing::StrictMock;
using ::testing::Return;

namespace UKControllerPluginTest {
    namespace IntentionCode {

        TEST(IntentionCodeCache, GetIntentionCodeForCallsignReturnsDefaultIfNoneFound)
        {
            IntentionCodeCache cache;
            EXPECT_TRUE("--" == cache.GetIntentionCodeForAircraft("BAW123"));
        }

        TEST(IntentionCodeCache, GetIntentionCodeForCallsignReturnsCodeCorrectly)
        {
            IntentionCodeCache cache;
            cache.RegisterAircraft("BAW123", IntentionCodeData("C2", false, true, "REDFA"));
            EXPECT_TRUE("C2" == cache.GetIntentionCodeForAircraft("BAW123"));
        }

        TEST(IntentionCodeCache, StartsEmpty)
        {
            IntentionCodeCache cache;
            EXPECT_EQ(0, cache.TotalCached());
        }

        TEST(IntentionCodeCache, HasIntentionCodeForAircraftReturnsFalseIfNoneFound)
        {
            IntentionCodeCache cache;
            EXPECT_FALSE(cache.HasIntentionCodeForAircraft("BAW123"));
        }

        TEST(IntentionCodeCache, RegisterAircraftAddsAircraftToCache)
        {
            IntentionCodeCache cache;
            cache.RegisterAircraft("BAW123", IntentionCodeData("D1", false, true, "KOK"));
            EXPECT_TRUE(cache.HasIntentionCodeForAircraft("BAW123"));
        }

        TEST(IntentionCodeCache, RegisterAircraftDoesNotDuplicateAircraft)
        {
            IntentionCodeCache cache;
            cache.RegisterAircraft("BAW123", IntentionCodeData("D1", false, true, "KOK"));
            cache.RegisterAircraft("BAW123", IntentionCodeData("D2", false, true, "KOK"));
            EXPECT_EQ(1, cache.TotalCached());
        }

        TEST(IntentionCodeCache, RegisterAircraftDoesNotChangeExistingCodes)
        {
            IntentionCodeCache cache;
            cache.RegisterAircraft("BAW123", IntentionCodeData("D1", false, true, "KOK"));
            cache.RegisterAircraft("BAW123", IntentionCodeData("D2", false, true, "KOK"));
            EXPECT_TRUE("D1" == cache.GetIntentionCodeForAircraft("BAW123"));
        }

        TEST(IntentionCodeCache, UnregisterAircraftRemovesAircraftFromCache)
        {
            IntentionCodeCache cache;
            cache.RegisterAircraft("BAW123", IntentionCodeData("D1", false, true, "KOK"));
            cache.UnregisterAircraft("BAW123");
            EXPECT_FALSE(cache.HasIntentionCodeForAircraft("BAW123"));
        }

        TEST(IntentionCodeCache, UnregisterAircraftDoesNothingIfDoesntExist)
        {
            IntentionCodeCache cache;
            cache.RegisterAircraft("BAW123", IntentionCodeData("D1", false, true, "KOK"));
            cache.UnregisterAircraft("BAW456");
            EXPECT_TRUE(cache.HasIntentionCodeForAircraft("BAW123"));
            EXPECT_EQ(1, cache.TotalCached());
        }

        TEST(IntentionCodeCache, IntentionCodeValidReturnsFalseIfNotCached)
        {
            IntentionCodeCache cache;
            StrictMock<MockEuroscopeExtractedRouteInterface> mockFlightplan;
            EXPECT_FALSE(cache.IntentionCodeValid("BAW123", mockFlightplan));
        }

        TEST(IntentionCodeCache, IntentionCodeValidReturnsTrueIfNotExiting)
        {
            IntentionCodeCache cache;
            StrictMock<MockEuroscopeExtractedRouteInterface> mockFlightplan;
            cache.RegisterAircraft("BAW123", IntentionCodeData("--", false, -1, ""));
            EXPECT_TRUE(cache.IntentionCodeValid("BAW123", mockFlightplan));
        }

        TEST(IntentionCodeCache, IntentionCodeValidReturnsTrueDirectGivenExitIfNotPassed)
        {
            IntentionCodeCache cache;
            StrictMock<MockEuroscopeExtractedRouteInterface> mockFlightplan;
            EXPECT_CALL(mockFlightplan, GetPointsAssignedIndex())
                .Times(1)
                .WillOnce(Return(7));

            EXPECT_CALL(mockFlightplan, GetPointsCalculatedIndex())
                .Times(1)
                .WillOnce(Return(4));


            cache.RegisterAircraft("BAW123", IntentionCodeData("--", true, 5, ""));
            EXPECT_TRUE(cache.IntentionCodeValid("BAW123", mockFlightplan));
        }

        TEST(IntentionCodeCache, IntentionCodeValidReturnsTrueDirectGivenButCloserToExit)
        {
            IntentionCodeCache cache;
            StrictMock<MockEuroscopeExtractedRouteInterface> mockFlightplan;
            EXPECT_CALL(mockFlightplan, GetPointsAssignedIndex())
                .Times(1)
                .WillOnce(Return(7));

            EXPECT_CALL(mockFlightplan, GetPointsCalculatedIndex())
                .Times(1)
                .WillOnce(Return(5));


            cache.RegisterAircraft("BAW123", IntentionCodeData("--", true, 5, ""));
            EXPECT_TRUE(cache.IntentionCodeValid("BAW123", mockFlightplan));
        }

        TEST(IntentionCodeCache, IntentionCodeValidReturnsFalseNoDirectPointPassed)
        {
            IntentionCodeCache cache;
            StrictMock<MockEuroscopeExtractedRouteInterface> mockFlightplan;
            EXPECT_CALL(mockFlightplan, GetPointsAssignedIndex())
                .Times(1)
                .WillOnce(Return(mockFlightplan.noDirect));

            EXPECT_CALL(mockFlightplan, GetPointDistanceInMinutes(5))
                .Times(1)
                .WillOnce(Return(mockFlightplan.pointPassed));


            cache.RegisterAircraft("BAW123", IntentionCodeData("--", true, 5, ""));
            EXPECT_FALSE(cache.IntentionCodeValid("BAW123", mockFlightplan));
        }

        TEST(IntentionCodeCache, IntentionCodeValidReturnsTrueNoDirectPointNotPassed)
        {
            IntentionCodeCache cache;
            StrictMock<MockEuroscopeExtractedRouteInterface> mockFlightplan;
            EXPECT_CALL(mockFlightplan, GetPointsAssignedIndex())
                .Times(1)
                .WillOnce(Return(mockFlightplan.noDirect));

            EXPECT_CALL(mockFlightplan, GetPointDistanceInMinutes(5))
                .Times(1)
                .WillOnce(Return(999));


            cache.RegisterAircraft("BAW123", IntentionCodeData("--", true, 5, ""));
            EXPECT_TRUE(cache.IntentionCodeValid("BAW123", mockFlightplan));
        }

        TEST(IntentionCodeCache, ClearCacheEmptiesCache)
        {
            IntentionCodeCache cache;
            cache.RegisterAircraft("BAW123", IntentionCodeData("D1", false, true, "KOK"));
            cache.RegisterAircraft("BAW456", IntentionCodeData("D1", false, true, "KOK"));
            cache.Clear();
            EXPECT_FALSE(cache.HasIntentionCodeForAircraft("BAW123"));
            EXPECT_FALSE(cache.HasIntentionCodeForAircraft("BAW456"));
            EXPECT_EQ(0, cache.TotalCached());
        }
    }  // namespace IntentionCode
}  // namespace UKControllerPluginTest
