#include "mapping/MappingRenderOptions.h"
#include "mapping/ToggleMappingOptionsRender.h"

using UKControllerPlugin::Mapping::MappingRenderOptions;
using UKControllerPlugin::Mapping::ToggleMappingOptionsRender;

namespace UKControllerPluginTest::Mapping {
    class ToggleMappingOptionsRenderTest : public testing::Test
    {
        public:
        ToggleMappingOptionsRenderTest() : options(std::make_shared<MappingRenderOptions>()), toggle(options, 123)
        {
        }

        testing::NiceMock<Euroscope::MockEuroscopeRadarScreenLoopbackInterface> radarScreen;
        std::shared_ptr<MappingRenderOptions> options;
        ToggleMappingOptionsRender toggle;
    };

    TEST_F(ToggleMappingOptionsRenderTest, LeftClickTogglesShowOptions)
    {
        EXPECT_FALSE(options->ShowOptions());
        toggle.LeftClick(radarScreen, 123, "", {}, {});
        EXPECT_TRUE(options->ShowOptions());
        toggle.LeftClick(radarScreen, 123, "", {}, {});
        EXPECT_FALSE(options->ShowOptions());
    }
} // namespace UKControllerPluginTest::Mapping
