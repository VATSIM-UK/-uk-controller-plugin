#include "DisplayRulesetFactoryInterface.h"
#include "MappingElement.h"
#include "MappingElementDrawerFactory.h"
#include "MappingElementFactory.h"
#include "MappingElementTypes.h"

namespace UKControllerPlugin::Mapping {

    MappingElementFactory::MappingElementFactory(
        std::shared_ptr<MappingElementDrawerFactory> drawerFactory,
        std::shared_ptr<DisplayRulesetFactoryInterface> displayRuleFactory)
        : drawerFactory(drawerFactory), displayRuleFactory(displayRuleFactory)
    {
        assert(drawerFactory && "drawerFactory not set in MappingElementFactory");
        assert(displayRuleFactory && "displayRuleFactory not set in MappingElementFactory");
    }

    auto MappingElementFactory::Make(const nlohmann::json& data) -> std::shared_ptr<MappingElement>
    {
        if (!DataIsValid(data)) {
            return nullptr;
        }

        const auto type = data.at("type").get<std::string>();
        if (!MappingElementTypes::TypeKnown(type)) {
            LogWarning("Detected mapping element of unknown type, ignoring");
            return nullptr;
        }

        return std::make_shared<MappingElement>(
            data.at("id").get<int>(),
            type,
            data.at("name").get<std::string>(),
            displayRuleFactory->Make(type, data.at("display_rules")),
            drawerFactory->Make(data));
    }

    /**
     * Checks that we have the minimum necessary data to build a mapping element.
     */
    auto MappingElementFactory::DataIsValid(const nlohmann::json& data) -> bool
    {
        return data.is_object() && data.contains("id") && data.at("id").is_number_integer() && data.contains("type") &&
               data.at("type").is_string() && data.contains("name") && data.at("name").is_string() &&
               data.contains("display_rules") && data.at("display_rules").is_array();
    }
} // namespace UKControllerPlugin::Mapping
