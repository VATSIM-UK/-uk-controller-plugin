#include "pch/pch.h"
#include "minstack/MinStackModule.h"
#include "mock/MockTaskRunnerInterface.h"
#include "mock/MockApiInterface.h"
#include "metar/MetarEventHandlerCollection.h"
#include "minstack/MinStackManager.h"
#include "curl/CurlResponse.h"
#include "minstack/TerminalControlArea.h"
#include "plugin/FunctionCallEventHandler.h"
#include "radarscreen/RadarRenderableCollection.h"
#include "radarscreen/ConfigurableDisplayCollection.h"
#include "graphics/GdiplusBrushes.h"
#include "euroscope/AsrEventHandlerCollection.h"
#include "curl/CurlRequest.h"
#include "websocket/WebsocketEventProcessorCollection.h"

using UKControllerPlugin::MinStack::MinStackModule;
using UKControllerPlugin::Metar::MetarEventHandlerCollection;
using UKControllerPluginTest::Api::MockApiInterface;
using UKControllerPluginTest::TaskManager::MockTaskRunnerInterface;
using UKControllerPlugin::MinStack::MinStackManager;
using UKControllerPlugin::Curl::CurlResponse;
using UKControllerPlugin::MinStack::TerminalControlArea;
using UKControllerPlugin::Plugin::FunctionCallEventHandler;
using UKControllerPlugin::RadarScreen::RadarRenderableCollection;
using UKControllerPlugin::RadarScreen::ConfigurableDisplayCollection;
using UKControllerPlugin::Windows::GdiplusBrushes;
using UKControllerPlugin::Euroscope::AsrEventHandlerCollection;
using UKControllerPlugin::Curl::CurlRequest;
using UKControllerPlugin::Websocket::WebsocketEventProcessorCollection;
using ::testing::StrictMock;
using ::testing::Return;
using ::testing::_;
using ::testing::Test;

namespace UKControllerModulesTest {
    namespace MinStack {

        class MinStackModuleTest : public Test
        {
            public:

                // For the plugin tests
                StrictMock<MockApiInterface> mockApi;
                MockTaskRunnerInterface mockRunner;
                MetarEventHandlerCollection metarEvents;
                WebsocketEventProcessorCollection websockets;
                std::shared_ptr<MinStackManager> manager;

                // For the radar screen tests
                FunctionCallEventHandler functionHandlers;
                MinStackManager managerObject;
                RadarRenderableCollection radarRenderables;
                ConfigurableDisplayCollection configruables;
                GdiplusBrushes brushes;
                AsrEventHandlerCollection userSettingHandlers;
        };

        TEST_F(MinStackModuleTest, BootstrapPluginCreatesTheManager)
        {
            nlohmann::json mslData;
            mslData["airfield"] = {
                {"EGLL", 8000}
            };
            mslData["tma"] = {
                {"LTMA", 7000}
            };
            EXPECT_CALL(this->mockApi, GetMinStackLevels())
                .Times(1)
                .WillRepeatedly(Return(mslData));

            MinStackModule::BootstrapPlugin(
                this->manager,
                this->metarEvents,
                this->mockRunner,
                this->mockApi,
                this->websockets
            );
            EXPECT_NO_THROW(manager->HasTerminalControlArea("TESTTMA"));
        }

        TEST_F(MinStackModuleTest, BootstrapPluginRegistersManagerForMetarEvents)
        {
            nlohmann::json mslData;
            mslData["airfield"] = {
                {"EGLL", 8000}
            };
            mslData["tma"] = {
                {"LTMA", 7000}
            };
            EXPECT_CALL(this->mockApi, GetMinStackLevels())
                .Times(1)
                .WillRepeatedly(Return(mslData));

            MinStackModule::BootstrapPlugin(
                this->manager,
                this->metarEvents,
                this->mockRunner,
                this->mockApi,
                this->websockets
            );
            EXPECT_EQ(1, metarEvents.CountHandlers());
        }

        TEST_F(MinStackModuleTest, BootstrapPluginRegistersManagerForWebsocketEvents)
        {
            nlohmann::json mslData;
            mslData["airfield"] = {
                {"EGLL", 8000}
            };
            mslData["tma"] = {
                {"LTMA", 7000}
            };
            EXPECT_CALL(this->mockApi, GetMinStackLevels())
                .Times(1)
                .WillRepeatedly(Return(mslData));

            MinStackModule::BootstrapPlugin(
                this->manager,
                this->metarEvents,
                this->mockRunner,
                this->mockApi,
                this->websockets
            );
            EXPECT_EQ(1, websockets.CountProcessorsForChannel("private-minstack-updates"));
        }

        TEST_F(MinStackModuleTest, BootstrapRadarScreenAddsToFunctionEvents)
        {
            MinStackModule::BootstrapRadarScreen(
                this->functionHandlers,
                this->managerObject,
                this->radarRenderables,
                this->configruables,
                this->brushes,
                this->userSettingHandlers
            );
            EXPECT_EQ(1, functionHandlers.CountCallbacks());
            EXPECT_EQ(0, functionHandlers.CountTagFunctions());
        }

        TEST_F(MinStackModuleTest, BootstrapRadarScreenAddsToRadarRenderablesInBeforeTagsPhase)
        {
            MinStackModule::BootstrapRadarScreen(
                this->functionHandlers,
                this->managerObject,
                this->radarRenderables,
                this->configruables,
                this->brushes,
                this->userSettingHandlers
            );
            EXPECT_EQ(1, radarRenderables.CountRenderers());
            EXPECT_EQ(1, radarRenderables.CountRenderersInPhase(radarRenderables.beforeTags));
        }

        TEST_F(MinStackModuleTest, BootstrapRadarScreenRegistersScreenObjects)
        {
            MinStackModule::BootstrapRadarScreen(
                this->functionHandlers,
                this->managerObject,
                this->radarRenderables,
                this->configruables,
                this->brushes,
                this->userSettingHandlers
            );
            EXPECT_EQ(3, radarRenderables.CountScreenObjects());
        }

        TEST_F(MinStackModuleTest, BootstrapRadarScreenAddsToConfigurableDisplays)
        {
            MinStackModule::BootstrapRadarScreen(
                this->functionHandlers,
                this->managerObject,
                this->radarRenderables,
                this->configruables,
                this->brushes,
                this->userSettingHandlers
            );
            EXPECT_EQ(1, configruables.CountDisplays());
        }

        TEST_F(MinStackModuleTest, BootstrapRadarScreenAddsToUserSettingEvents)
        {
            MinStackModule::BootstrapRadarScreen(
                this->functionHandlers,
                this->managerObject,
                this->radarRenderables,
                this->configruables,
                this->brushes,
                this->userSettingHandlers
            );
            EXPECT_EQ(1, userSettingHandlers.CountHandlers());
        }
    }  // namespace MinStack
}  // namespace UKControllerModulesTest
