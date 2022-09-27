#pragma once
namespace UKControllerPlugin::Mapping {
    class DisplayRule;

    /**
     * An interface for classes that make collections of display rules
     */
    class DisplayRulesetFactoryInterface
    {
        public:
        virtual ~DisplayRulesetFactoryInterface() = default;
        [[nodiscard]] virtual auto Make(const std::string& elementType, const nlohmann::json& data) const
            -> std::set<std::shared_ptr<DisplayRule>> = 0;
    };
} // namespace UKControllerPlugin::Mapping
