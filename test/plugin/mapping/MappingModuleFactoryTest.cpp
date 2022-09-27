#include "mapping/MappingModuleFactory.h"

using UKControllerPlugin::Mapping::MappingModuleFactory;

namespace UKControllerPluginTest::Mapping {
    class MappingModuleFactoryTest : public testing::Test
    {
        public:
        MappingModuleFactoryTest()
        {
            ON_CALL(dependencyLoader, LoadDependency).WillByDefault(testing::Return(nlohmann::json::array()));
        }

        testing::NiceMock<Dependency::MockDependencyLoader> dependencyLoader;
        MappingModuleFactory factory;
    };

    TEST_F(MappingModuleFactoryTest, ItReturnsAVrpDrawer)
    {
        EXPECT_NE(nullptr, factory.VrpDrawer("foo", EuroScopePlugIn::CPosition()));
    }

    TEST_F(MappingModuleFactoryTest, ItReturnsTheElementManager)
    {
        EXPECT_NE(nullptr, &factory.ElementManager(dependencyLoader));
    }

    TEST_F(MappingModuleFactoryTest, ItReturnsTheElementManagerAsASingleton)
    {
        EXPECT_EQ(&factory.ElementManager(dependencyLoader), &factory.ElementManager(dependencyLoader));
    }
} // namespace UKControllerPluginTest::Mapping
