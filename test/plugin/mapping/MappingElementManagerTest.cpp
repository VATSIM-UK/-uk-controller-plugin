#include "mapping/MappingElement.h"
#include "mapping/MappingElementManager.h"

using UKControllerPlugin::Mapping::DisplayRule;
using UKControllerPlugin::Mapping::MappingElement;
using UKControllerPlugin::Mapping::MappingElementInterface;
using UKControllerPlugin::Mapping::MappingElementManager;

namespace UKControllerPLuginTest::Mapping {
    class MappingElementManagerTest : public testing::Test
    {
        public:
        MappingElementManagerTest()
        {
            element1 = std::make_shared<MappingElement>(
                1, "vrp", "VRP One", std::set<std::shared_ptr<DisplayRule>>{}, nullptr);
            element2 = std::make_shared<MappingElement>(
                2, "not_vrp", "Not VRP One", std::set<std::shared_ptr<DisplayRule>>{}, nullptr);
            element3 = std::make_shared<MappingElement>(
                3, "vrp", "VRP Two", std::set<std::shared_ptr<DisplayRule>>{}, nullptr);
        }

        std::shared_ptr<MappingElement> element1;
        std::shared_ptr<MappingElement> element2;
        std::shared_ptr<MappingElement> element3;
        MappingElementManager manager;
    };

    TEST_F(MappingElementManagerTest, ItStartsEmpty)
    {
        EXPECT_EQ(0, manager.Count());
    }

    TEST_F(MappingElementManagerTest, ItAddsElements)
    {
        manager.Add(element1);
        manager.Add(element2);
        EXPECT_EQ(2, manager.Count());
    }

    TEST_F(MappingElementManagerTest, ItDoesntAddDuplicateElements)
    {
        manager.Add(element1);
        manager.Add(element1);
        manager.Add(element1);
        manager.Add(element2);
        manager.Add(element2);
        manager.Add(element2);
        EXPECT_EQ(2, manager.Count());
    }

    TEST_F(MappingElementManagerTest, ItReturnsElementByTypeAndId)
    {
        manager.Add(element1);
        manager.Add(element2);
        manager.Add(element3);

        EXPECT_EQ(element1, manager.GetByTypeAndId("vrp", 1));
    }

    TEST_F(MappingElementManagerTest, ItReturnsNullptrIfWrongId)
    {
        manager.Add(element1);
        manager.Add(element2);
        manager.Add(element3);

        EXPECT_EQ(nullptr, manager.GetByTypeAndId("not_vrp", 1));
    }

    TEST_F(MappingElementManagerTest, ItReturnsNullptrIfWrongType)
    {
        manager.Add(element1);
        manager.Add(element2);
        manager.Add(element3);

        EXPECT_EQ(nullptr, manager.GetByTypeAndId("vrp", 2));
    }

    TEST_F(MappingElementManagerTest, ItIteratesActiveElements)
    {
        manager.Add(element1);
        manager.Add(element2);

        std::set<MappingElementInterface*> expected{element1.get(), element2.get()};
        std::set<MappingElementInterface*> actual;
        manager.ForEachActiveElement([&actual](MappingElementInterface& element) { actual.insert(&element); });

        EXPECT_EQ(expected, actual);
    }
} // namespace UKControllerPLuginTest::Mapping
