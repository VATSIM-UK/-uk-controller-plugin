#include "DisplayRuleFactoryInterface.h"
#include "DisplayRulesetFactory.h"

namespace UKControllerPlugin::Mapping {
    DisplayRulesetFactory::DisplayRulesetFactory(std::shared_ptr<DisplayRuleFactoryInterface> ruleFactory)
        : ruleFactory(ruleFactory)
    {
        assert(ruleFactory && "ruleFactory not set in DisplayRulesetFactory");
    }

    auto DisplayRulesetFactory::Make(const std::string& elementType, const nlohmann::json& data) const
        -> std::set<std::shared_ptr<DisplayRule>>
    {
        std::set<std::shared_ptr<DisplayRule>> rules;

        for (const auto& ruleData : data) {
            const auto rule = ruleFactory->Make(elementType, ruleData);
            if (!rule) {
                LogWarning("Invalid mapping element display rule");
                continue;
            }

            rules.insert(rule);
        }

        return rules;
    }
} // namespace UKControllerPlugin::Mapping
