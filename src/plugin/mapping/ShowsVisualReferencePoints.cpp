#include "MappingRenderOptions.h"
#include "ShowsVisualReferencePoints.h"

namespace UKControllerPlugin::Mapping {
    ShowsVisualReferencePoints::ShowsVisualReferencePoints(std::shared_ptr<MappingRenderOptions> renderOptions)
        : renderOptions(std::move(renderOptions))
    {
    }

    auto ShowsVisualReferencePoints::Passes() -> bool
    {
        return renderOptions->ShowVisualReferencePoints();
    }
} // namespace UKControllerPlugin::Mapping
