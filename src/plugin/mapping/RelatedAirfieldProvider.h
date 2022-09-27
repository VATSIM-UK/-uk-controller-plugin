#pragma once

namespace UKControllerPlugin::Mapping {
    /**
     * Provides airfield to compare against related airfields.
     */
    class RelatedAirfieldProvider
    {
        public:
        virtual ~RelatedAirfieldProvider() = default;
        [[nodiscard]] virtual auto Airfields() const -> const std::set<int>& = 0;
    };
} // namespace UKControllerPlugin::Mapping
