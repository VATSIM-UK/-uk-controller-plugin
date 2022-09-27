#pragma once
#include "DisplayRule.h"

namespace UKControllerPlugin::Mapping {
    class MappingRenderOptions;
    
    /**
     * Should visual reference points be displayed.
     */
    class ShowsVisualReferencePoints : public DisplayRule
    {
        public:
        ShowsVisualReferencePoints(std::shared_ptr<MappingRenderOptions> renderOptions);
        auto Passes() -> bool override;

        private:
        
        // Options for rendering
        std::shared_ptr<MappingRenderOptions> renderOptions;
    };
} // namespace UKControllerPlugin::Mapping
