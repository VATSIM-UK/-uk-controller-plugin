#pragma once

namespace UKControllerPlugin::Mapping {
    class DefaultDisplayRulesetDelegatorFactory;
    class DisplayRulesetFactory;
    class DisplayRulesetFactoryInterface;
    class MappingRenderOptions;

    class DisplayRulesetFactoryFactory
    {
        public:
        [[nodiscard]] auto Make(std::shared_ptr<MappingRenderOptions> renderOptions) const
            -> std::shared_ptr<DisplayRulesetFactoryInterface>;

        private:
        [[nodiscard]] static auto GetDefaultRulesetFactories(std::shared_ptr<MappingRenderOptions> renderOptions)
            -> std::shared_ptr<DefaultDisplayRulesetDelegatorFactory>;
        
        [[nodiscard]] static auto GetDataDrivenRulesetFactories(std::shared_ptr<MappingRenderOptions> renderOptions)
            -> std::shared_ptr<DisplayRulesetFactory>;
    };
} // namespace UKControllerPlugin::Mapping
