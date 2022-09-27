#pragma once
#include "DisplayRuleFactoryInterface.h"

namespace UKControllerPlugin::Mapping {

    class MappingRenderOptions;

    class VisualReferencePointRelatedAirfieldFactory : public DisplayRuleFactoryInterface
    {
        public:
        VisualReferencePointRelatedAirfieldFactory(std::shared_ptr<MappingRenderOptions> renderOptions);
        [[nodiscard]] auto Make(const std::string& elementType, const nlohmann::json& data)
            -> std::shared_ptr<DisplayRule> override;

        private:
        [[nodiscard]] auto HasInvalidAirfields(const nlohmann::json& data) const -> bool;
        
        std::shared_ptr<MappingRenderOptions> renderOptions;
    };

} // namespace UKControllerPlugin::Mapping
