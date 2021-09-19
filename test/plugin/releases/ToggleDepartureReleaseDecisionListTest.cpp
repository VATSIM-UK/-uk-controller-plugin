#include "controller/ActiveCallsignCollection.h"
#include "controller/ControllerPositionCollection.h"
#include "dialog/DialogManager.h"
#include "releases/ToggleDepartureReleaseDecisionList.h"
#include "releases/DepartureReleaseDecisionList.h"
#include "releases/DepartureReleaseEventHandler.h"

using testing::Test;
using UKControllerPlugin::Releases::ToggleDepartureReleaseDecisionList;

namespace UKControllerPluginTest {
    namespace Releases {

        class ToggleDepartureReleaseDecisionListTest : public Test
        {
            public:
            ToggleDepartureReleaseDecisionListTest()
                : handler(
                      mockApi, taskRunner, mockPlugin, controllers, activeCallsigns, dialogManager, windows, 103, 104),
                  list(new UKControllerPlugin::Releases::DepartureReleaseDecisionList(
                      handler, mockPlugin, controllers, 3)),
                  dialogManager(dialogProvider)
            {
            }

            ToggleDepartureReleaseDecisionList GetList(bool alreadyToggled)
            {
                if (alreadyToggled) {
                    list->ToggleVisible();
                }

                return ToggleDepartureReleaseDecisionList(list, 2);
            }

            UKControllerPlugin::Releases::DepartureReleaseEventHandler handler;
            std::shared_ptr<UKControllerPlugin::Releases::DepartureReleaseDecisionList> list;
            UKControllerPlugin::Controller::ActiveCallsignCollection activeCallsigns;
            testing::NiceMock<Dialog::MockDialogProvider> dialogProvider;
            testing::NiceMock<Api::MockApiInterface> api;
            UKControllerPlugin::Dialog::DialogManager dialogManager;
            UKControllerPlugin::Controller::ControllerPositionCollection controllers;
            testing::NiceMock<Euroscope::MockEuroscopePluginLoopbackInterface> mockPlugin;
            testing::NiceMock<Api::MockApiInterface> mockApi;
            testing::NiceMock<Windows::MockWinApi> windows;
            TaskManager::MockTaskRunnerInterface taskRunner;
        };

        TEST_F(ToggleDepartureReleaseDecisionListTest, ItReturnsAConfigurationItemNotToggled)
        {
            const ToggleDepartureReleaseDecisionList list = GetList(true);

            UKControllerPlugin::Plugin::PopupMenuItem expected{
                "Toggle Departure Release Decision List", "", 2, EuroScopePlugIn::POPUP_ELEMENT_CHECKED, false, false};

            EXPECT_EQ(expected, list.GetConfigurationMenuItem());
        }

        TEST_F(ToggleDepartureReleaseDecisionListTest, ItReturnsAConfigurationItemToggled)
        {
            const ToggleDepartureReleaseDecisionList list = GetList(false);

            UKControllerPlugin::Plugin::PopupMenuItem expected{
                "Toggle Departure Release Decision List",
                "",
                2,
                EuroScopePlugIn::POPUP_ELEMENT_UNCHECKED,
                false,
                false};

            EXPECT_EQ(expected, list.GetConfigurationMenuItem());
        }

        TEST_F(ToggleDepartureReleaseDecisionListTest, ClickingTheItemTogglesTheList)
        {
            ToggleDepartureReleaseDecisionList toggleList = GetList(true);
            EXPECT_TRUE(list->IsVisible());
            toggleList.Configure(1, "", {});
            EXPECT_FALSE(list->IsVisible());
            toggleList.Configure(1, "", {});
            EXPECT_TRUE(list->IsVisible());
        }
    } // namespace Releases
} // namespace UKControllerPluginTest
