#pragma once

namespace UKControllerPlugin::Mapping {
    class DisplayRule;

    /**
     * An interface for classes that want to build display rules.
     */
    class DisplayRuleFactoryInterface
    {
        public:
        virtual ~DisplayRuleFactoryInterface() = default;
        [[nodiscard]] virtual auto Make(const std::string& elementType, const nlohmann::json& data)
            -> std::shared_ptr<DisplayRule> = 0;
    };
} // namespace UKControllerPlugin::Mapping
