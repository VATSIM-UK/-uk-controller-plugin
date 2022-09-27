#include "mapping/MappingModuleFactory.h"
#include "mapping/MappingElement.h"
#include "mapping/MappingElementDrawer.h"
#include "mapping/MappingElementManager.h"
#include "mapping/MappingElementManagerFactory.h"
#include "mapping/VisualReferencePoint.h"

using UKControllerPlugin::Mapping::ElementValid;
using UKControllerPlugin::Mapping::MakeMappingElementManager;
using UKControllerPlugin::Mapping::MappingElementDrawer;
using UKControllerPlugin::Mapping::MappingModuleFactory;
using UKControllerPlugin::Mapping::VisualReferencePoint;

namespace UKControllerPluginTest::Mapping {
    class MappingElementManagerFactoryTest : public testing::Test
    {
        public:
        MappingElementManagerFactoryTest()
        {
            ON_CALL(dependencyLoader, LoadDependency("DEPENDENCY_MAPPING_ELEMENTS", nlohmann::json::array()))
                .WillByDefault(testing::Return(nlohmann::json::array()));
        }

        [[nodiscard]] static auto
        GetJson(const nlohmann::json& overridingData = nlohmann::json::object(), const std::string& keyToRemove = "")
            -> nlohmann::json
        {
            nlohmann::json json{
                {"id", 1},
                {"type", "visual_reference_point"},
                {"latitude", 1.1},
                {"longitude", 2.2},
                {"name", "M5 Avon Bridge"}};

            if (overridingData.is_object()) {
                json.update(overridingData);
            } else {
                json = overridingData;
            }

            if (!keyToRemove.empty()) {
                json.erase(json.find(keyToRemove));
            }

            return json;
        }

        testing::NiceMock<Dependency::MockDependencyLoader> dependencyLoader;
        MappingModuleFactory moduleFactory;
    };

    TEST_F(MappingElementManagerFactoryTest, ElementIsValid)
    {
        EXPECT_TRUE(ElementValid(GetJson()));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfNotObject)
    {
        EXPECT_FALSE(ElementValid(nlohmann::json::array()));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfIdMissing)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object(), "id")));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfIdNotInteger)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object({{"id", "abc"}}))));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfTypeMissing)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object(), "type")));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfTypeNotString)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object({{"type", 123}}))));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfTypeNotValid)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object({{"type", "not_visual_reference_point"}}))));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfLatitudeMissing)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object(), "latitude")));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfLatitudeNotNumber)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object({{"latitude", "abc"}}))));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfLongitudeMissing)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object(), "longitude")));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfLongitudeNotNumber)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object({{"longitude", "abc"}}))));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfNameMissing)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object(), "name")));
    }

    TEST_F(MappingElementManagerFactoryTest, ElementIsNotValidIfNameNotString)
    {
        EXPECT_FALSE(ElementValid(GetJson(nlohmann::json::object({{"name", 123}}))));
    }

    TEST_F(MappingElementManagerFactoryTest, ItBuildsDefaultEmptyCollection)
    {
        EXPECT_EQ(0, MakeMappingElementManager(moduleFactory, dependencyLoader)->Count());
    }

    TEST_F(MappingElementManagerFactoryTest, ItReturnsEmptyCollectionIfDependencyNotArray)
    {
        ON_CALL(dependencyLoader, LoadDependency("DEPENDENCY_MAPPING_ELEMENTS", nlohmann::json::array()))
            .WillByDefault(testing::Return(nlohmann::json::object()));

        EXPECT_EQ(0, MakeMappingElementManager(moduleFactory, dependencyLoader)->Count());
    }

    TEST_F(MappingElementManagerFactoryTest, ItBuildsCollection)
    {
        nlohmann::json dependency = nlohmann::json::array();
        dependency.push_back(GetJson());
        dependency.push_back(GetJson(nlohmann::json::object({{"id", 2}, {"name", "VRP Two"}})));

        ON_CALL(dependencyLoader, LoadDependency("DEPENDENCY_MAPPING_ELEMENTS", nlohmann::json::array()))
            .WillByDefault(testing::Return(dependency));

        const auto manager = MakeMappingElementManager(moduleFactory, dependencyLoader);
        EXPECT_EQ(2, manager->Count());
        const auto element1 = manager->GetByTypeAndId("visual_reference_point", 1);
        EXPECT_NE(nullptr, element1);
        EXPECT_EQ(1, element1->Id());
        EXPECT_EQ("visual_reference_point", element1->Type());
        EXPECT_EQ("M5 Avon Bridge", element1->Label());
        auto drawer1 = static_cast<VisualReferencePoint*>(element1->Drawer().get());
        EXPECT_DOUBLE_EQ(1.1, drawer1->Position().m_Latitude);
        EXPECT_DOUBLE_EQ(2.2, drawer1->Position().m_Longitude);
        EXPECT_EQ("M5 Avon Bridge", drawer1->Label());

        const auto element2 = manager->GetByTypeAndId("visual_reference_point", 2);
        EXPECT_NE(nullptr, element2);
        EXPECT_EQ(2, element2->Id());
        EXPECT_EQ("visual_reference_point", element2->Type());
        EXPECT_EQ("VRP Two", element2->Label());
        auto drawer2 = static_cast<VisualReferencePoint*>(element2->Drawer().get());
        EXPECT_DOUBLE_EQ(1.1, drawer2->Position().m_Latitude);
        EXPECT_DOUBLE_EQ(2.2, drawer2->Position().m_Longitude);
        EXPECT_EQ("VRP Two", drawer2->Label());
    }

    TEST_F(MappingElementManagerFactoryTest, ItIgnoresBadElementsInDependency)
    {
        nlohmann::json dependency = nlohmann::json::array();
        dependency.push_back(GetJson(nlohmann::json::object({{"id", "abc"}, {"name", "VRP Two"}})));
        dependency.push_back(GetJson(nlohmann::json::object({{"name", 123}})));

        ON_CALL(dependencyLoader, LoadDependency("DEPENDENCY_MAPPING_ELEMENTS", nlohmann::json::array()))
            .WillByDefault(testing::Return(dependency));

        const auto manager = MakeMappingElementManager(moduleFactory, dependencyLoader);
        EXPECT_EQ(0, manager->Count());
    }
} // namespace UKControllerPluginTest::Mapping
