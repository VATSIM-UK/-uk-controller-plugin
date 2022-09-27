#include "mapping/MappingElement.h"

using UKControllerPlugin::Mapping::DisplayRule;
using UKControllerPlugin::Mapping::MappingElement;

namespace UKControllerPluginTest::Mapping {
    class MappingElementTest : public testing::Test
    {
        public:
        MappingElementTest()
            : displayRule1(std::make_shared<testing::NiceMock<Mapping::MockDisplayRule>>()),
              displayRule2(std::make_shared<testing::NiceMock<Mapping::MockDisplayRule>>()),
              displayRules({displayRule1, displayRule2}),
              drawer(std::make_shared<testing::NiceMock<Mapping::MockMappingElementDrawer>>()),
              element(1, "visual_reference_point", "M5 Avon Bridge", displayRules, drawer)
        {
        }

        testing::NiceMock<Euroscope::MockEuroscopeRadarScreenLoopbackInterface> radarScreen;
        testing::NiceMock<Windows::MockGraphicsInterface> graphics;
        std::shared_ptr<testing::NiceMock<Mapping::MockDisplayRule>> displayRule1;
        std::shared_ptr<testing::NiceMock<Mapping::MockDisplayRule>> displayRule2;
        std::set<std::shared_ptr<DisplayRule>> displayRules;
        std::shared_ptr<testing::NiceMock<Mapping::MockMappingElementDrawer>> drawer;
        MappingElement element;
    };

    TEST_F(MappingElementTest, ItHasAnId)
    {
        EXPECT_EQ(1, element.Id());
    }

    TEST_F(MappingElementTest, ItHasAType)
    {
        EXPECT_EQ("visual_reference_point", element.Type());
    }

    TEST_F(MappingElementTest, ItHasALabel)
    {
        EXPECT_EQ("M5 Avon Bridge", element.Label());
    }

    TEST_F(MappingElementTest, ItHasADrawer)
    {
        EXPECT_EQ(drawer, element.Drawer());
    }

    TEST_F(MappingElementTest, ItShouldDisplayIfAllRulesPass)
    {
        ON_CALL(*displayRule1, Passes()).WillByDefault(testing::Return(true));

        ON_CALL(*displayRule2, Passes()).WillByDefault(testing::Return(true));

        EXPECT_TRUE(element.ShouldDisplay());
    }

    TEST_F(MappingElementTest, ItShouldNotDisplayIfARuleDoesNotPass)
    {
        ON_CALL(*displayRule1, Passes()).WillByDefault(testing::Return(true));

        ON_CALL(*displayRule2, Passes()).WillByDefault(testing::Return(false));

        EXPECT_FALSE(element.ShouldDisplay());
    }

    TEST_F(MappingElementTest, ItDraws)
    {
        EXPECT_CALL(*drawer, Draw(testing::_, testing::_)).Times(1);

        element.Draw(graphics, radarScreen);
    }
} // namespace UKControllerPluginTest::Mapping
