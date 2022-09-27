#include "approach/ApproachBootstrapProvider.h"
#include "bootstrap/BootstrapProviderCollection.h"
#include "bootstrap/BootstrapProviderCollectionFactory.h"
#include "mapping/MappingBootstrapProvider.h"

using UKControllerPlugin::Approach::ApproachBootstrapProvider;
using UKControllerPlugin::Bootstrap::Make;
using UKControllerPlugin::Mapping::MappingBootstrapProvider;

namespace UKControllerPluginTest::Bootstrap {
    class BootstrapProviderCollectionFactoryTest : public testing::Test
    {
        public:
        template <typename T> void AssertHasProvider()
        {
            EXPECT_TRUE(Make()->HasProvider([](const BootstrapProviderInterface& provider) -> bool {
                try {
                    static_cast<void>(dynamic_cast<const T&>(provider));
                    return true;
                } catch (std::bad_cast&) {
                    return false;
                }
            }));
        }
    };

    TEST_F(BootstrapProviderCollectionFactoryTest, TestItHasApproachModule)
    {
        AssertHasProvider<ApproachBootstrapProvider>();
    }

    TEST_F(BootstrapProviderCollectionFactoryTest, TestItHasMappingModule)
    {
        AssertHasProvider<MappingBootstrapProvider>();
    }
} // namespace UKControllerPluginTest::Bootstrap
