#include "DisplayRuleElementTypeDelegatorFactory.h"

namespace UKControllerPlugin::Mapping {
    DisplayRuleElementTypeDelegatorFactory::DisplayRuleElementTypeDelegatorFactory(
        std::map<std::string, std::shared_ptr<DisplayRuleFactoryInterface>> factories)
        : factories(std::move(factories))
    {
    }

    auto DisplayRuleElementTypeDelegatorFactory::Make(const std::string& elementType, const nlohmann::json& data)
        -> std::shared_ptr<DisplayRule>
    {
        if (!factories.contains(elementType)) {
            throw std::invalid_argument("Invalid element type for display rule");
        }

        return factories.at(elementType)->Make(elementType, data);
    }
} // namespace UKControllerPlugin::Mapping
