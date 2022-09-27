#include "DefaultDisplayRulesetDelegatorFactory.h"

namespace UKControllerPlugin::Mapping {

    DefaultDisplayRulesetDelegatorFactory::DefaultDisplayRulesetDelegatorFactory(
        const std::map<std::string, std::shared_ptr<DisplayRulesetFactoryInterface>> factories)
        : factories(std::move(factories))
    {
    }

    auto DefaultDisplayRulesetDelegatorFactory::Make(const std::string& elementType, const nlohmann::json& data) const
        -> std::set<std::shared_ptr<DisplayRule>>
    {
        if (!factories.contains(elementType)) {
            throw std::invalid_argument("No default display ruleset factory for element type " + elementType);
        }

        return factories.at(elementType)->Make(elementType, data);
    }
} // namespace UKControllerPlugin::Mapping
