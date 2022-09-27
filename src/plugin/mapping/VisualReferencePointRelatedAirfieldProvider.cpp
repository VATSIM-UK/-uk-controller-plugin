#include "MappingRenderOptions.h"
#include "VisualReferencePointRelatedAirfieldProvider.h"

namespace UKControllerPlugin::Mapping {

    VisualReferencePointRelatedAirfieldProvider::VisualReferencePointRelatedAirfieldProvider(
        std::shared_ptr<MappingRenderOptions> renderOptions)
        : renderOptions(std::move(renderOptions))
    {
    }

    auto VisualReferencePointRelatedAirfieldProvider::Airfields() const -> const std::set<int>&
    {
        return renderOptions->VisualReferencePointAirfields();
    }
} // namespace UKControllerPlugin::Mapping
