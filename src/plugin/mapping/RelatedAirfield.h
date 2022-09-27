#pragma once
#include "DisplayRule.h"

namespace UKControllerPlugin::Mapping {
    class RelatedAirfieldProvider;

    /**
     * Checks if related airfields are selected for the mapping element.
     */
    class RelatedAirfield : public DisplayRule
    {
        public:
        RelatedAirfield(std::shared_ptr<RelatedAirfieldProvider> provider, std::set<int> airfields);
        auto Passes() -> bool override;

        private:
        // Provides the airfields to compare against
        std::shared_ptr<RelatedAirfieldProvider> provider;

        // The airfields that are related
        std::set<int> airfields;
    };
} // namespace UKControllerPlugin::Mapping
