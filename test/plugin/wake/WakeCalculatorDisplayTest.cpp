#include "euroscope/UserSetting.h"
#include "wake/WakeCalculatorDisplay.h"
#include "wake/WakeCalculatorOptions.h"

using UKControllerPlugin::Euroscope::UserSetting;
using UKControllerPlugin::Wake::WakeCalculatorDisplay;
using UKControllerPlugin::Wake::WakeCalculatorOptions;

namespace UKControllerPluginTest::Wake {
    class WakeCalculatorDisplayTest : public testing::Test
    {
        public:
        WakeCalculatorDisplayTest()
            : userSettings(mockAsrProvider),
              leadCallsignSelector(std::make_shared<testing::NiceMock<List::MockPopupList>>()),
              followingCallsignSelector(std::make_shared<testing::NiceMock<List::MockPopupList>>()),
              wakesSchemeSelector(std::make_shared<testing::NiceMock<List::MockPopupList>>()),
              options(std::make_shared<WakeCalculatorOptions>()),
              display(options, leadCallsignSelector, followingCallsignSelector, wakesSchemeSelector, plugin, 1)
        {
        }

        testing::NiceMock<Euroscope::MockUserSettingProviderInterface> mockAsrProvider;
        UserSetting userSettings;
        testing::NiceMock<Euroscope::MockEuroscopeRadarScreenLoopbackInterface> radarScreen;
        testing::NiceMock<Euroscope::MockEuroscopePluginLoopbackInterface> plugin;
        std::shared_ptr<testing::NiceMock<List::MockPopupList>> leadCallsignSelector;
        std::shared_ptr<testing::NiceMock<List::MockPopupList>> followingCallsignSelector;
        std::shared_ptr<testing::NiceMock<List::MockPopupList>> wakesSchemeSelector;
        std::shared_ptr<WakeCalculatorOptions> options;
        WakeCalculatorDisplay display;
    };

    TEST_F(WakeCalculatorDisplayTest, ItHasAMenuItem)
    {
        EXPECT_EQ("Display Wake Turbulence Calculator", display.MenuItem());
    }

    TEST_F(WakeCalculatorDisplayTest, ItCanBeViewToggled)
    {
        EXPECT_FALSE(display.IsVisible());
        display.Toggle();
        EXPECT_TRUE(display.IsVisible());
        display.Toggle();
        EXPECT_FALSE(display.IsVisible());
    }

    TEST_F(WakeCalculatorDisplayTest, ItCanBeCollapsedByClickButton)
    {
        EXPECT_FALSE(display.IsCollapsed());
        display.LeftClick(radarScreen, 1, "collapseButton", {1, 2}, {});
        EXPECT_TRUE(display.IsCollapsed());
        display.LeftClick(radarScreen, 1, "collapseButton", {1, 2}, {});
        EXPECT_FALSE(display.IsCollapsed());
    }

    TEST_F(WakeCalculatorDisplayTest, ItCanBeClosedByClickButton)
    {
        if (!display.IsVisible()) {
            display.Toggle();
        }
        EXPECT_TRUE(display.IsVisible());
        display.LeftClick(radarScreen, 1, "closeButton", {1, 2}, {});
        EXPECT_FALSE(display.IsVisible());
    }

    TEST_F(WakeCalculatorDisplayTest, ItHasADefaultPosition)
    {
        const auto position = display.Position();
        EXPECT_EQ(200, position.x);
        EXPECT_EQ(200, position.y);
    }

    TEST_F(WakeCalculatorDisplayTest, ItCanBeMoved)
    {
        display.Move({300, 400, 500, 600}, "");
        const auto position = display.Position();
        EXPECT_EQ(300, position.x);
        EXPECT_EQ(400, position.y);
    }

    TEST_F(WakeCalculatorDisplayTest, ItCanHaveItsPositionResetToDefault)
    {
        display.Move({300, 400, 500, 600}, "");
        display.ResetPosition();
        const auto position = display.Position();
        EXPECT_EQ(200, position.x);
        EXPECT_EQ(200, position.y);
    }

    TEST_F(WakeCalculatorDisplayTest, AsrLoadingLoadsPosition)
    {
        EXPECT_CALL(mockAsrProvider, GetKey(testing::_)).Times(2).WillRepeatedly(testing::Return(""));

        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorXPosition")).Times(1).WillOnce(testing::Return("250"));

        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorYPosition")).Times(1).WillOnce(testing::Return("150"));

        display.AsrLoadedEvent(userSettings);
        const auto position = display.Position();
        EXPECT_EQ(250, position.x);
        EXPECT_EQ(150, position.y);
    }

    TEST_F(WakeCalculatorDisplayTest, AsrLoadingLoadsVisibility)
    {
        EXPECT_CALL(mockAsrProvider, GetKey(testing::_)).Times(3).WillRepeatedly(testing::Return(""));

        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorVisibility")).Times(1).WillOnce(testing::Return("1"));

        display.AsrLoadedEvent(userSettings);
        EXPECT_TRUE(display.IsVisible());
    }

    TEST_F(WakeCalculatorDisplayTest, AsrLoadingLoadsCollapsed)
    {
        EXPECT_CALL(mockAsrProvider, GetKey(testing::_)).Times(3).WillRepeatedly(testing::Return(""));

        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorCollapsed")).Times(1).WillOnce(testing::Return("1"));

        display.AsrLoadedEvent(userSettings);
        EXPECT_TRUE(display.IsCollapsed());
    }

    TEST_F(WakeCalculatorDisplayTest, AsrLoadingLoadsDefaultPosition)
    {
        display.Move({300, 400, 500, 600}, "");
        EXPECT_CALL(mockAsrProvider, GetKey(testing::_)).Times(2).WillRepeatedly(testing::Return(""));
        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorXPosition")).Times(1).WillOnce(testing::Return(""));
        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorYPosition")).Times(1).WillOnce(testing::Return(""));

        display.AsrLoadedEvent(userSettings);
        const auto position = display.Position();
        EXPECT_EQ(200, position.x);
        EXPECT_EQ(200, position.y);
    }

    TEST_F(WakeCalculatorDisplayTest, AsrLoadingLoadsDefaultVisibility)
    {
        display.Toggle();
        EXPECT_CALL(mockAsrProvider, GetKey(testing::_)).Times(3).WillRepeatedly(testing::Return(""));
        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorVisibility")).Times(1).WillOnce(testing::Return(""));

        display.AsrLoadedEvent(userSettings);
        EXPECT_FALSE(display.IsVisible());
    }

    TEST_F(WakeCalculatorDisplayTest, AsrLoadingLoadsDefaultCollapsed)
    {
        display.Toggle();
        EXPECT_CALL(mockAsrProvider, GetKey(testing::_)).Times(3).WillRepeatedly(testing::Return(""));
        EXPECT_CALL(mockAsrProvider, GetKey("wakeCalculatorCollapsed")).Times(1).WillOnce(testing::Return(""));

        display.AsrLoadedEvent(userSettings);
        EXPECT_FALSE(display.IsCollapsed());
    }

    TEST_F(WakeCalculatorDisplayTest, AsrClosingSavesFields)
    {
        display.Toggle();
        display.Move({300, 400, 500, 600}, "");
        EXPECT_CALL(mockAsrProvider, SetKey("wakeCalculatorVisibility", "Wake Calculator Visibility", "1")).Times(1);
        EXPECT_CALL(mockAsrProvider, SetKey("wakeCalculatorXPosition", "Wake Calculator X Position", "300")).Times(1);
        EXPECT_CALL(mockAsrProvider, SetKey("wakeCalculatorYPosition", "Wake Calculator Y Position", "400")).Times(1);
        EXPECT_CALL(mockAsrProvider, SetKey("wakeCalculatorCollapsed", "Wake Calculator Collapsed", "0")).Times(1);

        display.AsrClosingEvent(userSettings);
    }

    TEST_F(WakeCalculatorDisplayTest, LeadCallsignClickTriggersList)
    {
        EXPECT_CALL(*leadCallsignSelector, Trigger(PointEq(POINT({1, 2})))).Times(1);

        display.LeftClick(radarScreen, 1, "leadcallsign", {1, 2}, {});
    }

    TEST_F(WakeCalculatorDisplayTest, FollowingCallsignClickTriggersList)
    {
        EXPECT_CALL(*followingCallsignSelector, Trigger(PointEq(POINT({1, 2})))).Times(1);

        display.LeftClick(radarScreen, 1, "followcallsign", {1, 2}, {});
    }

    TEST_F(WakeCalculatorDisplayTest, SchemeClickTriggersList)
    {
        EXPECT_CALL(*wakesSchemeSelector, Trigger(PointEq(POINT({1, 2})))).Times(1);

        display.LeftClick(radarScreen, 1, "scheme", {1, 2}, {});
    }

    TEST_F(WakeCalculatorDisplayTest, IntermediateClickToggles)
    {
        EXPECT_FALSE(options->Intermediate());
        display.LeftClick(radarScreen, 1, "intermediate", {1, 2}, {});
        EXPECT_TRUE(options->Intermediate());
        display.LeftClick(radarScreen, 1, "intermediate", {1, 2}, {});
        EXPECT_FALSE(options->Intermediate());
    }

    TEST_F(WakeCalculatorDisplayTest, ModeTogglesMode)
    {
        EXPECT_FALSE(options->Arrivals());
        display.LeftClick(radarScreen, 1, "mode", {1, 2}, {});
        EXPECT_TRUE(options->Arrivals());
        display.LeftClick(radarScreen, 1, "mode", {1, 2}, {});
        EXPECT_FALSE(options->Arrivals());
    }

    TEST_F(WakeCalculatorDisplayTest, ModeToggleResetsCallsigns)
    {
        options->LeadAircraft("abc");
        options->FollowingAircraft("def");
        display.LeftClick(radarScreen, 1, "mode", {1, 2}, {});
        EXPECT_TRUE(options->LeadAircraft().empty());
        EXPECT_TRUE(options->FollowingAircraft().empty());
    }
} // namespace UKControllerPluginTest::Wake
