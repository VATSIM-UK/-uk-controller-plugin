#include "DefaultDisplayRulesetDelegatorFactory.h"
#include "DisplayRuleFactoryFactory.h"
#include "DisplayRulesetAggregatorFactory.h"
#include "DisplayRulesetFactory.h"
#include "DisplayRulesetFactoryFactory.h"
#include "MappingElementTypes.h"
#include "VisualReferencePointDefaultDisplayRulesetFactory.h"

namespace UKControllerPlugin::Mapping {

    auto DisplayRulesetFactoryFactory::Make(std::shared_ptr<MappingRenderOptions> renderOptions) const
        -> std::shared_ptr<DisplayRulesetFactoryInterface>
    {
        assert(renderOptions && "Render options not set in DisplayRulesetFactoryFactory");

        return std::make_shared<DisplayRulesetAggregatorFactory>(
            GetDataDrivenRulesetFactories(renderOptions), GetDefaultRulesetFactories(renderOptions));
    }

    auto DisplayRulesetFactoryFactory::GetDefaultRulesetFactories(std::shared_ptr<MappingRenderOptions> renderOptions)
        -> std::shared_ptr<DefaultDisplayRulesetDelegatorFactory>
    {
        const std::map<std::string, std::shared_ptr<DisplayRulesetFactoryInterface>> factories{
            {MappingElementTypes::VisualReferencePoint(),
             std::make_shared<VisualReferencePointDefaultDisplayRulesetFactory>(renderOptions)}};

        return std::make_shared<DefaultDisplayRulesetDelegatorFactory>(factories);
    }

    auto
    DisplayRulesetFactoryFactory::GetDataDrivenRulesetFactories(std::shared_ptr<MappingRenderOptions> renderOptions)
        -> std::shared_ptr<DisplayRulesetFactory>
    {
        return std::make_shared<DisplayRulesetFactory>(DisplayRuleFactoryFactory().Make(renderOptions));
    }
} // namespace UKControllerPlugin::Mapping
