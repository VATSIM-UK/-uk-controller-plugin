#include "RelatedAirfield.h"
#include "RelatedAirfieldProvider.h"

namespace UKControllerPlugin::Mapping {

    RelatedAirfield::RelatedAirfield(std::shared_ptr<RelatedAirfieldProvider> provider, std::set<int> airfields)
        : provider(std::move(provider)), airfields(std::move(airfields))
    {
    }

    auto RelatedAirfield::Passes() -> bool
    {
        const auto& selectedAirfields = provider->Airfields();
        for (const auto& airfield : airfields) {
            if (selectedAirfields.find(airfield) != selectedAirfields.cend()) {
                return true;
            }
        }

        return false;
    }
} // namespace UKControllerPlugin::Mapping
