#pragma once
#include "DisplayRule.h"

namespace UKControllerPlugin::Mapping {
    class MappingRenderOptions;

    /**
     * Determines whether a VRP should render.
     */
    class VisualReferencePointShouldRender : public DisplayRule
    {
        public:
        VisualReferencePointShouldRender(std::shared_ptr<MappingRenderOptions> renderOptions);
        [[nodiscard]] auto Passes() -> bool override;

        private:
        // Render options
        std::shared_ptr<MappingRenderOptions> renderOptions;
    };
} // namespace UKControllerPlugin::Mapping
