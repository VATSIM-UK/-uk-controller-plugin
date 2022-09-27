#include "VisualReferencePointDefaultDisplayRulesetFactory.h"
#include "VisualReferencePointShouldRender.h"

namespace UKControllerPlugin::Mapping {
    VisualReferencePointDefaultDisplayRulesetFactory::VisualReferencePointDefaultDisplayRulesetFactory(
        std::shared_ptr<MappingRenderOptions> renderOptions)
        : renderOptions(renderOptions)
    {
        assert(renderOptions && "Render options not set in VisualReferencePointDefaultDisplayRulesetFactory");
    }

    auto VisualReferencePointDefaultDisplayRulesetFactory::Make(
        const std::string& elementType, const nlohmann::json& data) const -> std::set<std::shared_ptr<DisplayRule>>
    {
        return {std::make_shared<VisualReferencePointShouldRender>(renderOptions)};
    }
} // namespace UKControllerPlugin::Mapping
