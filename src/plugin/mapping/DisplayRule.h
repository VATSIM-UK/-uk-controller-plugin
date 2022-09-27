#pragma once

namespace UKControllerPlugin::Mapping {
    /**
     * A rule as to whether a particular mapping element should be displayed.
     */
    class DisplayRule
    {
        public:
        virtual ~DisplayRule() = default;

        /**
         * Returns true if the rule passes and thus the element should
         * be rendered.
         */
        [[nodiscard]] virtual auto Passes() -> bool = 0;
    };
} // namespace UKControllerPlugin::Mapping
