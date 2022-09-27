#pragma once

namespace UKControllerPlugin::Mapping {
    class DisplayRulesetFactoryInterface;
    class MappingElementDrawerFactory;
    class MappingElement;

    class MappingElementFactory
    {
        public:
        MappingElementFactory(
            std::shared_ptr<MappingElementDrawerFactory> drawerFactory,
            std::shared_ptr<DisplayRulesetFactoryInterface> displayRuleFactory
        );
        [[nodiscard]] auto Make(const nlohmann::json& data) -> std::shared_ptr<MappingElement>;

        private:
        [[nodiscard]] static auto DataIsValid(const nlohmann::json& data) -> bool;

        // Builds drawers
        std::shared_ptr<MappingElementDrawerFactory> drawerFactory;
        
        // Builds rulesets for display
        std::shared_ptr<DisplayRulesetFactoryInterface> displayRuleFactory;
    };
} // namespace UKControllerPlugin::Mapping
