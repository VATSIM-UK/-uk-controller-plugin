#pragma once

namespace UKControllerPlugin::Mapping {
    class DisplayRuleFactoryInterface;
    class MappingRenderOptions;

    /**
     * Builds the display rule factory structure
     */
    class DisplayRuleFactoryFactory
    {
        public:
        [[nodiscard]] auto Make(std::shared_ptr<MappingRenderOptions> renderOptions)
            -> std::shared_ptr<DisplayRuleFactoryInterface>;

        private:
        auto RuleTypeFactories(std::shared_ptr<MappingRenderOptions> renderOptions) const
            -> std::map<std::string, std::shared_ptr<DisplayRuleFactoryInterface>>;
        auto RelatedAirfieldFactories(const std::shared_ptr<MappingRenderOptions>& renderOptions) const
            -> std::shared_ptr<DisplayRuleFactoryInterface>;
    };
} // namespace UKControllerPlugin::Mapping
