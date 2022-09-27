#pragma once

namespace UKControllerPlugin::Components {

    /**
     * Provides the information required to have a checkbox.
     */
    class CheckboxProviderInterface
    {
        public:
        virtual ~CheckboxProviderInterface();
        [[nodiscard]] virtual auto Label() -> std::string = 0;
        virtual void StateChanged(bool checked) = 0;
    };
} // namespace UKControllerPlugin::Components
