#include "approach/ApproachModuleFactory.h"
#include "bootstrap/ModuleFactories.h"
#include "mapping/MappingModuleFactory.h"

using UKControllerPlugin::Bootstrap::ModuleFactories;

namespace UKControllerPluginTest::Bootstrap {
    class ModuleFactoriesTest : public testing::Test
    {
        public:
        ModuleFactories factories;
    };

    TEST_F(ModuleFactoriesTest, ItReturnsApproachFactoryAsSingleton)
    {
        EXPECT_NE(nullptr, &factories.Approach());
        EXPECT_EQ(&factories.Approach(), &factories.Approach());
    }

    TEST_F(ModuleFactoriesTest, ItReturnsMappingFactoryAsSingleton)
    {
        EXPECT_NE(nullptr, &factories.Mapping());
        EXPECT_EQ(&factories.Mapping(), &factories.Mapping());
    }
} // namespace UKControllerPluginTest::Bootstrap
