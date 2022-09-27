#include "MappingRenderOptions.h"
#include "VisualReferencePointCheckboxProvider.h"

namespace UKControllerPlugin::Mapping {

    VisualReferencePointCheckboxProvider::VisualReferencePointCheckboxProvider(
        std::shared_ptr<MappingRenderOptions> renderOptions)
        : renderOptions(renderOptions)
    {
        assert(renderOptions && "Render options not set in VisualReferencePointCheckboxProvider");
    }

    auto VisualReferencePointCheckboxProvider::Label() -> std::string
    {
        return "Display VRPs";
    }

    void VisualReferencePointCheckboxProvider::StateChanged(bool checked)
    {
        renderOptions->ShowVisualReferencePoints(checked);
    }
} // namespace UKControllerPlugin::Mapping
