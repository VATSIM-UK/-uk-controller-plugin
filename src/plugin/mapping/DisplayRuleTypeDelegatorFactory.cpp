#include "DisplayRuleTypeDelegatorFactory.h"

namespace UKControllerPlugin::Mapping {
    DisplayRuleTypeDelegatorFactory::DisplayRuleTypeDelegatorFactory(
        std::map<std::string, std::shared_ptr<DisplayRuleFactoryInterface>> factories)
        : factories(std::move(factories))
    {
    }

    auto DisplayRuleTypeDelegatorFactory::Make(const std::string& elementType, const nlohmann::json& data)
        -> std::shared_ptr<DisplayRule>
    {
        const auto ruleType = data.at("type").get<std::string>();
        if (!factories.contains(ruleType)) {
            throw std::invalid_argument("Invalid display rule type");
        }

        return factories.at(ruleType)->Make(elementType, data);
    }
} // namespace UKControllerPlugin::Mapping
