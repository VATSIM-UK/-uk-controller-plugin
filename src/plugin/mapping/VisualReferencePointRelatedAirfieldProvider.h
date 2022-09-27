#pragma once
#include "RelatedAirfieldProvider.h"

namespace UKControllerPlugin::Mapping {
    class MappingRenderOptions;

    /**
     * Provides airfields related to visual reference points
     */
    class VisualReferencePointRelatedAirfieldProvider : public RelatedAirfieldProvider
    {
        public:
        VisualReferencePointRelatedAirfieldProvider(std::shared_ptr<MappingRenderOptions> renderOptions);
        [[nodiscard]] auto Airfields() const -> const std::set<int>& override;

        private:
        // Rendering options
        std::shared_ptr<MappingRenderOptions> renderOptions;
    };
} // namespace UKControllerPlugin::Mapping
