#include "pch/pch.h"
#include "squawk/SquawkEventHandler.h"
#include "squawk/SquawkGenerator.h"
#include "mock/MockEuroScopeCFlightplanInterface.h"
#include "curl/CurlResponse.h"
#include "spdlog/sinks/null_sink.h"
#include "mock/MockTaskRunnerInterface.h"
#include "mock/MockEuroScopeCRadarTargetInterface.h"
#include "flightplan/StoredFlightplanCollection.h"
#include "flightplan/StoredFlightplan.h"
#include "controller/ActiveCallsignCollection.h"
#include "airfield/AirfieldOwnershipManager.h"
#include "airfield/AirfieldCollection.h"
#include "controller/ActiveCallsign.h"
#include "controller/ControllerPosition.h"
#include "airfield/Airfield.h"
#include "mock/MockEuroscopePluginLoopbackInterface.h"
#include "api/ApiRequestBuilder.h"
#include "curl/CurlRequest.h"
#include "mock/MockWinApi.h"
#include "mock/MockApiInterface.h"
#include "squawk/SquawkAssignment.h"
#include "login/Login.h"
#include "controller/ControllerStatusEventHandlerCollection.h"
#include "timedevent/DeferredEventHandler.h"
#include "euroscope/UserSetting.h"
#include "mock/MockUserSettingProviderInterface.h"
#include "euroscope/GeneralSettingsEntries.h"
#include "squawk/ApiSquawkAllocation.h"
#include "squawk/ApiSquawkAllocationHandler.h"

using UKControllerPlugin::Squawk::SquawkEventHandler;
using UKControllerPluginTest::Euroscope::MockEuroScopeCFlightPlanInterface;
using UKControllerPluginTest::Euroscope::MockEuroscopePluginLoopbackInterface;
using UKControllerPlugin::Squawk::SquawkGenerator;
using UKControllerPlugin::Curl::CurlResponse;
using UKControllerPluginTest::TaskManager::MockTaskRunnerInterface;
using UKControllerPluginTest::Euroscope::MockEuroScopeCFlightPlanInterface;
using UKControllerPluginTest::Euroscope::MockEuroScopeCRadarTargetInterface;
using UKControllerPlugin::Flightplan::StoredFlightplanCollection;
using UKControllerPlugin::Flightplan::StoredFlightplan;
using UKControllerPlugin::Controller::ActiveCallsignCollection;
using UKControllerPlugin::Airfield::AirfieldOwnershipManager;
using UKControllerPlugin::Airfield::AirfieldCollection;
using UKControllerPlugin::Controller::ActiveCallsign;
using UKControllerPlugin::Controller::ControllerPosition;
using UKControllerPlugin::Airfield::Airfield;
using UKControllerPlugin::Squawk::SquawkAssignment;
using UKControllerPlugin::Api::ApiRequestBuilder;
using UKControllerPlugin::Curl::CurlRequest;
using UKControllerPluginTest::Windows::MockWinApi;
using UKControllerPluginTest::Api::MockApiInterface;
using UKControllerPlugin::Controller::Login;
using UKControllerPlugin::Controller::ControllerStatusEventHandlerCollection;
using UKControllerPlugin::TimedEvent::DeferredEventHandler;
using UKControllerPlugin::Euroscope::UserSetting;
using UKControllerPluginTest::Euroscope::MockUserSettingProviderInterface;
using UKControllerPlugin::Euroscope::GeneralSettingsEntries;
using UKControllerPlugin::Squawk::ApiSquawkAllocation;
using UKControllerPlugin::Squawk::ApiSquawkAllocationHandler;

using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;
using ::testing::Throw;
using ::testing::_;

namespace UKControllerPluginTest {
    namespace Squawk {

        class SquawkEventHandlerTest : public Test
        {
            public:

                SquawkEventHandlerTest()
                    : apiSquawkAllocations(new ApiSquawkAllocationHandler(this->pluginLoopback)),
                    login(this->pluginLoopback, ControllerStatusEventHandlerCollection()),
                    controller("EGKK_APP", 126.820, "APP", { "EGKK" }),
                    airfieldOwnership(this->airfields, this->activeCallsigns),
                    assignmentRules(
                        this->plans,
                        this->pluginLoopback,
                        this->airfieldOwnership,
                        this->activeCallsigns,
                        false
                    ),
                    generator(
                        this->mockApi,
                        &this->taskRunner,
                        this->assignmentRules,
                        this->activeCallsigns,
                        this->plans,
                        this->apiSquawkAllocations
                    ),
                    handler(
                        this->generator,
                        this->activeCallsigns,
                        this->plans,
                        this->pluginLoopback,
                        this->login,
                        this->deferredEvents,
                        false
                    )
                {

                }

                void SetUp()
                {
                    this->mockFlightplan.reset(new NiceMock<MockEuroScopeCFlightPlanInterface>);
                    this->mockRadarTarget.reset(new NiceMock<MockEuroScopeCRadarTargetInterface>);

                    this->airfields.AddAirfield(std::unique_ptr<Airfield>(new Airfield("EGKK", { "EGKK_APP" })));
                    this->activeCallsigns.AddUserCallsign(
                        ActiveCallsign(
                            "EGKK_APP",
                            "Testy McTestface",
                            this->controller
                        )
                    );
                    this->airfieldOwnership.RefreshOwner("EGKK");

                    // By default, lets assume we've been logged in for a while.
                    this->login.SetLoginTime(std::chrono::system_clock::now() - std::chrono::minutes(5));
                }

                void expectGeneralAssignment()
                {
                    ON_CALL(*mockFlightplan, GetCallsign())
                        .WillByDefault(Return("BAW1252"));

                    ON_CALL(*mockFlightplan, GetOrigin())
                        .WillByDefault(Return("EGKK"));

                    ON_CALL(*mockFlightplan, GetDestination())
                        .WillByDefault(Return("EGPF"));

                    ON_CALL(*this->mockFlightplan, HasAssignedSquawk())
                        .WillByDefault(Return(false));

                    ON_CALL(*this->mockFlightplan, IsTrackedByUser())
                        .WillByDefault(Return(true));

                    ON_CALL(*this->mockFlightplan, IsTracked())
                        .WillByDefault(Return(true));

                    ON_CALL(*this->mockRadarTarget, GetFlightLevel())
                        .WillByDefault(Return(this->assignmentRules.maxAssignmentAltitude + 1));

                    EXPECT_CALL(*mockFlightplan, SetSquawk("7000"))
                        .Times(1);

                    ApiSquawkAllocation allocation{ "BAW1252", "1423" };
                    EXPECT_CALL(this->mockApi, GetAssignedSquawk("BAW1252"))
                        .Times(1)
                        .WillOnce(Return(allocation));

                    ON_CALL(this->pluginLoopback, GetRadarTargetForCallsign("BAW1252"))
                        .WillByDefault(Return(this->mockRadarTarget));

                    ON_CALL(this->pluginLoopback, GetFlightplanForCallsign("BAW1252"))
                        .WillByDefault(Return(mockFlightplan));
                }

                void expectLocalAssignment(void)
                {
                    ON_CALL(*mockFlightplan, GetCallsign())
                        .WillByDefault(Return("GATWF"));

                    ON_CALL(*mockFlightplan, GetOrigin())
                        .WillByDefault(Return("EGKK"));

                    ON_CALL(*mockFlightplan, GetDestination())
                        .WillByDefault(Return("EGPF"));

                    ON_CALL(*this->mockFlightplan, HasAssignedSquawk())
                        .WillByDefault(Return(false));

                    ON_CALL(*this->mockFlightplan, IsTrackedByUser())
                        .WillByDefault(Return(true));

                    ON_CALL(*mockFlightplan, GetFlightRules())
                        .WillByDefault(Return("V"));

                    EXPECT_CALL(*mockFlightplan, SetSquawk("7000"))
                        .Times(1);

                    ApiSquawkAllocation allocation{ "BAW1252", "7261" };
                    EXPECT_CALL(this->mockApi, GetAssignedSquawk("GATWF"))
                        .Times(1)
                        .WillOnce(Return(allocation));

                    ON_CALL(this->pluginLoopback, GetFlightplanForCallsign("GATWF"))
                        .WillByDefault(Return(mockFlightplan));
                }

                void AssertGeneralAssignment()
                {
                    ApiSquawkAllocation allocation{ "BAW1252", "1423" };
                    EXPECT_EQ(1, this->apiSquawkAllocations->Count());
                    EXPECT_TRUE(allocation == this->apiSquawkAllocations->First());
                }

                void AssertLocalAssignment()
                {
                    ApiSquawkAllocation allocation{ "BAW1252", "7261" };
                    EXPECT_EQ(1, this->apiSquawkAllocations->Count());
                    EXPECT_TRUE(allocation == this->apiSquawkAllocations->First());
                }

                DeferredEventHandler deferredEvents;
                Login login;
                NiceMock<MockEuroscopePluginLoopbackInterface> pluginLoopback;
                std::shared_ptr<NiceMock<MockEuroScopeCFlightPlanInterface>> mockFlightplan;
                std::shared_ptr<NiceMock<MockEuroScopeCRadarTargetInterface>> mockRadarTarget;
                std::shared_ptr<ApiSquawkAllocationHandler> apiSquawkAllocations;
                NiceMock<MockApiInterface> mockApi;
                NiceMock<MockWinApi> mockWinApi;
                NiceMock<MockTaskRunnerInterface> taskRunner;
                StoredFlightplanCollection plans;
                SquawkGenerator generator;
                SquawkAssignment assignmentRules;
                ActiveCallsignCollection activeCallsigns;
                AirfieldOwnershipManager airfieldOwnership;
                ControllerPosition controller;
                AirfieldCollection airfields;
                SquawkEventHandler handler;
        };

        TEST_F(SquawkEventHandlerTest, ItDefaultsToUserSquawksOn)
        {
            EXPECT_TRUE(this->handler.UserAllowedSquawkAssignment());
        }

        TEST_F(SquawkEventHandlerTest, ItUpdatesBasedOnUserSettings)
        {
            NiceMock<MockUserSettingProviderInterface> userSettingProvider;
            UserSetting userSetting(userSettingProvider);

            EXPECT_CALL(userSettingProvider, GetKey(GeneralSettingsEntries::squawkToggleSettingsKey))
                .Times(1)
                .WillOnce(Return("0"));

            this->handler.UserSettingsUpdated(userSetting);
            EXPECT_FALSE(this->handler.UserAllowedSquawkAssignment());
        }

        TEST_F(SquawkEventHandlerTest, ItDefaultsToTrueIfNoUserSetting)
        {
            NiceMock<MockUserSettingProviderInterface> userSettingProvider;
            UserSetting userSetting(userSettingProvider);

            EXPECT_CALL(userSettingProvider, GetKey(GeneralSettingsEntries::squawkToggleSettingsKey))
                .Times(1)
                .WillOnce(Return("0"));

            NiceMock<MockUserSettingProviderInterface> userSettingProviderNoValue;
            EXPECT_CALL(userSettingProviderNoValue, GetKey(GeneralSettingsEntries::squawkToggleSettingsKey))
                .Times(1)
                .WillOnce(Return(""));

            UserSetting userSettingNoValue(userSettingProviderNoValue);

            this->handler.UserSettingsUpdated(userSetting);
            this->handler.UserSettingsUpdated(userSettingNoValue);
            EXPECT_TRUE(this->handler.UserAllowedSquawkAssignment());
        }

        TEST_F(SquawkEventHandlerTest, FlightplanEventDoesNothingIfUserToggleNotOn)
        {
            NiceMock<MockUserSettingProviderInterface> userSettingProvider;
            UserSetting userSetting(userSettingProvider);

            EXPECT_CALL(userSettingProvider, GetKey(GeneralSettingsEntries::squawkToggleSettingsKey))
                .Times(1)
                .WillOnce(Return("0"));

            this->handler.UserSettingsUpdated(userSetting);

            StrictMock<MockEuroScopeCFlightPlanInterface> mockFp;
            StrictMock<MockEuroScopeCRadarTargetInterface> mockRt;
            EXPECT_NO_THROW(this->handler.FlightPlanEvent(mockFp, mockRt));
        }

        TEST_F(SquawkEventHandlerTest, FlightplanEventDefersFor10SecondsIfNotLoggedInLongEnough)
        {
            ON_CALL(*this->mockFlightplan, GetCallsign())
                .WillByDefault(Return("BAW123"));

            this->login.SetLoginTime(std::chrono::system_clock::now());
            this->handler.FlightPlanEvent(*this->mockFlightplan, *this->mockRadarTarget);

            EXPECT_EQ(1, this->deferredEvents.Count());
            int64_t seconds = std::chrono::duration_cast<std::chrono::seconds> (
                this->deferredEvents.NextEventTime() - std::chrono::system_clock::now()
            )
                .count();
            EXPECT_LE(seconds, 15);
            EXPECT_GT(seconds, 13);
        }

        TEST_F(SquawkEventHandlerTest, FlightplanEventReassignsOldSquawk)
        {
           StoredFlightplan plan("BAW123", "EGKK", "EGPF");
           plan.SetPreviouslyAssignedSquawk("3421");
           this->plans.UpdatePlan(plan);

           ON_CALL(*this->mockFlightplan, HasAssignedSquawk())
               .WillByDefault(Return(false));

           ON_CALL(*this->mockFlightplan, IsTrackedByUser())
               .WillByDefault(Return(true));

           ON_CALL(*this->mockFlightplan, GetCallsign())
               .WillByDefault(Return("BAW123"));

           EXPECT_CALL(*this->mockFlightplan, SetSquawk("3421"))
               .Times(1);

           this->handler.FlightPlanEvent(*this->mockFlightplan, *this->mockRadarTarget);
        }

        TEST_F(SquawkEventHandlerTest, FlightplanEventAssignsLocalSquawk)
        {
           this->expectLocalAssignment();
           this->handler.FlightPlanEvent(*this->mockFlightplan, *this->mockRadarTarget);
           this->AssertLocalAssignment();
        }

        TEST_F(SquawkEventHandlerTest, FlightplanEventAssignsGeneralSquawk)
        {
           this->expectGeneralAssignment();
           this->handler.FlightPlanEvent(*this->mockFlightplan, *this->mockRadarTarget);
           this->AssertGeneralAssignment();
        }

        TEST_F(SquawkEventHandlerTest, FlightplanControllerDataUpdateSetsPreviousSquawkIfDataTypeSquawk)
        {
           StoredFlightplan plan("BAW1252", "EGKK", "EGPF");
           plan.SetPreviouslyAssignedSquawk("3421");
           this->plans.UpdatePlan(plan);

           ON_CALL(*this->mockFlightplan, GetCallsign())
               .WillByDefault(Return("BAW1252"));

           ON_CALL(*this->mockFlightplan, HasAssignedSquawk())
               .WillByDefault(Return(true));

           ON_CALL(*this->mockFlightplan, GetAssignedSquawk())
               .WillByDefault(Return("1426"));

           this->handler.ControllerFlightPlanDataEvent(*this->mockFlightplan, EuroScopePlugIn::CTR_DATA_TYPE_SQUAWK);
           EXPECT_TRUE(this->plans.GetFlightplanForCallsign("BAW1252").GetPreviouslyAssignedSquawk() == "1426");
        }

        TEST_F(SquawkEventHandlerTest, FlightplanControllerDataUpdateDoesNothingIfDataTypeNotSquawk)
        {
           StoredFlightplan plan("BAW1252", "EGKK", "EGPF");
           plan.SetPreviouslyAssignedSquawk("3413");
           this->plans.UpdatePlan(plan);

           ON_CALL(*this->mockFlightplan, GetCallsign())
               .WillByDefault(Return("BAW1252"));

           ON_CALL(*this->mockFlightplan, HasAssignedSquawk())
               .WillByDefault(Return(true));

           ON_CALL(*this->mockFlightplan, GetAssignedSquawk())
               .WillByDefault(Return("1426"));

           this->handler.ControllerFlightPlanDataEvent(
               *this->mockFlightplan,
               EuroScopePlugIn::CTR_DATA_TYPE_DEPARTURE_SEQUENCE
            );
           EXPECT_FALSE(this->plans.GetFlightplanForCallsign("BAW1252").GetPreviouslyAssignedSquawk() == "1426");
        }

        TEST_F(SquawkEventHandlerTest, SquawkReycleGeneralForcesSquawkReset)
        {
           ON_CALL(*mockFlightplan, GetCallsign())
               .WillByDefault(Return("BAW1252"));

           ON_CALL(*mockFlightplan, GetOrigin())
               .WillByDefault(Return("EGKK"));

           ON_CALL(*mockFlightplan, GetDestination())
               .WillByDefault(Return("EGPF"));

            ON_CALL(this->pluginLoopback, GetFlightplanForCallsign("BAW1252"))
               .WillByDefault(Return(mockFlightplan));

           EXPECT_CALL(*mockFlightplan, SetSquawk("7000"))
               .Times(1);

           EXPECT_CALL(this->mockApi, CreateGeneralSquawkAssignment("BAW1252", "EGKK", "EGPF"))
               .Times(1)
               .WillOnce(Return(ApiSquawkAllocation{ "BAW1252", "1423" }));

           this->handler.SquawkReycleGeneral(*this->mockFlightplan, *this->mockRadarTarget);
           this->AssertGeneralAssignment();
        }

        TEST_F(SquawkEventHandlerTest, SquawkReycleLocalForcesSquawkReset)
        {
           ON_CALL(*mockFlightplan, GetCallsign())
               .WillByDefault(Return("GATWF"));

           ON_CALL(*mockFlightplan, GetOrigin())
               .WillByDefault(Return("EGKK"));

           ON_CALL(*mockFlightplan, GetDestination())
               .WillByDefault(Return("EGPF"));

           ON_CALL(*mockFlightplan, GetFlightRules())
               .WillByDefault(Return("V"));

           ON_CALL(this->pluginLoopback, GetFlightplanForCallsign("GATWF"))
               .WillByDefault(Return(mockFlightplan));

           EXPECT_CALL(*mockFlightplan, SetSquawk("7000"))
               .Times(1);

           EXPECT_CALL(this->mockApi, CreateLocalSquawkAssignment("GATWF", "EGKK", "V"))
               .Times(1)
               .WillOnce(Return(ApiSquawkAllocation{ "BAW1252", "7261" }));

           this->handler.SquawkRecycleLocal(*this->mockFlightplan, *this->mockRadarTarget);
           this->AssertLocalAssignment();
        }

        TEST_F(SquawkEventHandlerTest, TimedEventTriggerDoesNothingIfUserNotActive)
        {
           this->plans.UpdatePlan(StoredFlightplan("BAW1252", "EGKK", "EGPF"));
           ON_CALL(this->pluginLoopback, GetFlightplanForCallsign(_))
               .WillByDefault(Throw(std::exception("test")));
           SquawkEventHandler handler(
               this->generator,
               ActiveCallsignCollection(),
               this->plans,
               this->pluginLoopback,
               this->login,
               this->deferredEvents,
               true
           );
           EXPECT_NO_THROW(handler.TimedEventTrigger());
        }

        TEST_F(SquawkEventHandlerTest, TimedEventTriggerDoesNothingIfAutoAssignDisabled)
        {
           this->plans.UpdatePlan(StoredFlightplan("BAW1252", "EGKK", "EGPF"));
           ON_CALL(this->pluginLoopback, GetFlightplanForCallsign(_))
               .WillByDefault(Throw(std::exception("test")));
           SquawkEventHandler handler(
               this->generator,
               this->activeCallsigns,
               this->plans,
               this->pluginLoopback,
               this->login,
               this->deferredEvents,
               true
           );
           EXPECT_NO_THROW(handler.TimedEventTrigger());
        }

        TEST_F(SquawkEventHandlerTest, TimedEventTriggerDoesNothingIfUserToggleOff)
        {
            NiceMock<MockUserSettingProviderInterface> userSettingProvider;
            UserSetting userSetting(userSettingProvider);

            EXPECT_CALL(userSettingProvider, GetKey(GeneralSettingsEntries::squawkToggleSettingsKey))
                .Times(1)
                .WillOnce(Return("0"));

            this->plans.UpdatePlan(StoredFlightplan("BAW1252", "EGKK", "EGPF"));
            ON_CALL(this->pluginLoopback, GetFlightplanForCallsign(_))
                .WillByDefault(Throw(std::exception("test")));

            this->handler.UserSettingsUpdated(userSetting);
            EXPECT_NO_THROW(handler.TimedEventTrigger());
        }

        TEST_F(SquawkEventHandlerTest, TimedEventTriggerDoesNothingIfFlightplanHasAssignedSquawk)
        {
           ON_CALL(*this->mockFlightplan, HasAssignedSquawk)
               .WillByDefault(Return(true));

           ON_CALL(this->pluginLoopback, GetFlightplanForCallsign)
               .WillByDefault(Return(this->mockFlightplan));

           EXPECT_NO_THROW(handler.TimedEventTrigger());
        }

        TEST_F(SquawkEventHandlerTest, TimedEventTriggerDoesNothingIfFlightplanNotTrackedByUser)
        {
           ON_CALL(*this->mockFlightplan, HasAssignedSquawk)
               .WillByDefault(Return(false));

           ON_CALL(*this->mockFlightplan, IsTrackedByUser)
               .WillByDefault(Return(false));

           ON_CALL(this->pluginLoopback, GetFlightplanForCallsign)
               .WillByDefault(Return(this->mockFlightplan));

           EXPECT_NO_THROW(handler.TimedEventTrigger());
        }

        TEST_F(SquawkEventHandlerTest, TimedEventTriggerDoesSquawkAssignmentWhereAppropriate)
        {
           this->plans.UpdatePlan(StoredFlightplan("BAW1252", "EGKK", "EGPF"));

           ON_CALL(*this->mockFlightplan, HasAssignedSquawk)
               .WillByDefault(Return(false));

           ON_CALL(*this->mockFlightplan, IsTrackedByUser)
               .WillByDefault(Return(true));

           ON_CALL(*this->mockRadarTarget, GetFlightLevel())
               .WillByDefault(Return(999999));

           this->expectGeneralAssignment();
           handler.TimedEventTrigger();
           this->AssertGeneralAssignment();
        }
    }  // namespace Squawk
}  // namespace UKControllerPluginTest
