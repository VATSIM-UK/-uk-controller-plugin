#pragma once
#include "DisplayRulesetFactoryInterface.h"

namespace UKControllerPlugin::Mapping {
    class DisplayRule;
    class DisplayRuleFactoryInterface;

    /**
     * Creates a set of display rules
     */
    class DisplayRulesetFactory : public DisplayRulesetFactoryInterface
    {
        public:
        DisplayRulesetFactory(std::shared_ptr<DisplayRuleFactoryInterface> ruleFactory);
        [[nodiscard]] auto Make(const std::string& elementType, const nlohmann::json& data) const
            -> std::set<std::shared_ptr<DisplayRule>> override;

        private:
        // Builds individual rules
        std::shared_ptr<DisplayRuleFactoryInterface> ruleFactory;
    };

} // namespace UKControllerPlugin::Mapping
