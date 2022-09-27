#include "DisplayRuleElementTypeDelegatorFactory.h"
#include "DisplayRuleFactoryFactory.h"
#include "DisplayRuleTypeDelegatorFactory.h"
#include "MappingElementTypes.h"
#include "VisualReferencePointRelatedAirfieldFactory.h"

namespace UKControllerPlugin::Mapping {

    auto DisplayRuleFactoryFactory::Make(std::shared_ptr<MappingRenderOptions> renderOptions)
        -> std::shared_ptr<DisplayRuleFactoryInterface>
    {
        return std::make_shared<DisplayRuleTypeDelegatorFactory>(RuleTypeFactories(std::move(renderOptions)));
    }
    auto DisplayRuleFactoryFactory::RelatedAirfieldFactories(const std::shared_ptr<MappingRenderOptions>& renderOptions)
        const -> std::shared_ptr<DisplayRuleFactoryInterface>
    {
        const auto factories = std::map<std::string, std::shared_ptr<DisplayRuleFactoryInterface>>{
            {MappingElementTypes::VisualReferencePoint(),
             std::make_shared<VisualReferencePointRelatedAirfieldFactory>(renderOptions)}};

        return std::make_shared<DisplayRuleElementTypeDelegatorFactory>(factories);
    }

    auto DisplayRuleFactoryFactory::RuleTypeFactories(std::shared_ptr<MappingRenderOptions> renderOptions) const
        -> std::map<std::string, std::shared_ptr<DisplayRuleFactoryInterface>>
    {
        return {{"related_airfield", RelatedAirfieldFactories(std::move(renderOptions))}};
    }
} // namespace UKControllerPlugin::Mapping
