#include "MappingRenderOptions.h"
#include "VisualReferencePointShouldRender.h"

namespace UKControllerPlugin::Mapping {

    VisualReferencePointShouldRender::VisualReferencePointShouldRender(
        std::shared_ptr<MappingRenderOptions> renderOptions)
        : renderOptions(renderOptions)
    {
        assert(renderOptions && "Render options not set in VisualReferencePointShouldRender");
    }

    auto VisualReferencePointShouldRender::Passes() -> bool
    {
        return renderOptions->ShowVisualReferencePoints();
    }
} // namespace UKControllerPlugin::Mapping
