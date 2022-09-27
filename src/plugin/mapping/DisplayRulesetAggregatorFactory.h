#pragma once
#include "DisplayRulesetFactoryInterface.h"

namespace UKControllerPlugin::Mapping {

    /**
     * Combines the data-driven and default display rulesets into one
     */
    class DisplayRulesetAggregatorFactory : public DisplayRulesetFactoryInterface
    {
        public:
        DisplayRulesetAggregatorFactory(
            std::shared_ptr<DisplayRulesetFactoryInterface> dataDrivenFactories,
            std::shared_ptr<DisplayRulesetFactoryInterface> defaultFactories);
        [[nodiscard]] auto Make(const std::string& elementType, const nlohmann::json& data) const
            -> std::set<std::shared_ptr<DisplayRule>> override;

        // Factories that are driven specifically by the data
        std::shared_ptr<DisplayRulesetFactoryInterface> dataDrivenFactories;

        // Factories for default rules
        std::shared_ptr<DisplayRulesetFactoryInterface> defaultFactories;
    };
} // namespace UKControllerPlugin::Mapping
