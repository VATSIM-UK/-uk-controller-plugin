#pragma once
#include "DisplayRulesetFactoryInterface.h"

namespace UKControllerPlugin::Mapping {
    class MappingRenderOptions;

    /**
     * Builds the default rulset for VRPS
     */
    class VisualReferencePointDefaultDisplayRulesetFactory : public DisplayRulesetFactoryInterface
    {
        public:
        VisualReferencePointDefaultDisplayRulesetFactory(std::shared_ptr<MappingRenderOptions> renderOptions);
        [[nodiscard]] auto Make(const std::string& elementType, const nlohmann::json& data) const
            -> std::set<std::shared_ptr<DisplayRule>> override;

        private:
        // The render options
        const std::shared_ptr<MappingRenderOptions> renderOptions;
    };
} // namespace UKControllerPlugin::Mapping
