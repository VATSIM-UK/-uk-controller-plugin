#include "mapping/MappingBootstrapProvider.h"

using UKControllerPlugin::Mapping::MappingBootstrapProvider;

namespace UKControllerPluginTest::Mapping {
    class MappingBootstrapProviderTest : public BootstrapProviderTestCase
    {
        public:
        MappingBootstrapProvider provider;
    };

    TEST_F(MappingBootstrapProviderTest, ItBootstrapsElementRendererToRadarScreen)
    {
        this->RunBootstrapRadarScreen(provider);
        EXPECT_EQ(1, renderers.CountRenderersInPhase(renderers.beforeTags));
    }

    TEST_F(MappingBootstrapProviderTest, ItBootstrapsOptionsRenderersToRadarScreen)
    {
        this->RunBootstrapRadarScreen(provider);
        EXPECT_EQ(2, renderers.CountRenderersInPhase(renderers.afterLists));
    }
} // namespace UKControllerPluginTest::Mapping
