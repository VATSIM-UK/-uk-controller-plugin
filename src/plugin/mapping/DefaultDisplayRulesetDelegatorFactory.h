#pragma once
#include "DisplayRulesetFactoryInterface.h"

namespace UKControllerPlugin::Mapping {
    class DefaultDisplayRulesetDelegatorFactory : public DisplayRulesetFactoryInterface
    {
        public:
        DefaultDisplayRulesetDelegatorFactory(
            const std::map<std::string, std::shared_ptr<DisplayRulesetFactoryInterface>> factories);
        auto Make(const std::string& elementType, const nlohmann::json& data) const
            -> std::set<std::shared_ptr<DisplayRule>> override;

        private:
        // Factories for delegation
        const std::map<std::string, std::shared_ptr<DisplayRulesetFactoryInterface>> factories;
    };
} // namespace UKControllerPlugin::Mapping
