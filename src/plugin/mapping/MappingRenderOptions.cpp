#include "MappingRenderOptions.h"

namespace UKControllerPlugin::Mapping {

    void MappingRenderOptions::ShowVisualReferencePoints(bool show)
    {
        this->showVisualReferencePoints = show;
    }

    auto MappingRenderOptions::ShowVisualReferencePoints() const -> bool
    {
        return this->showVisualReferencePoints;
    }

    void MappingRenderOptions::ShowOptions(bool show)
    {
        this->showOptions = show;
    }

    auto MappingRenderOptions::ShowOptions() const -> bool
    {
        return this->showOptions;
    }

    auto MappingRenderOptions::VisualReferencePointAirfields() const -> const std::set<int>&
    {
        return this->visualReferencePointAirfields;
    }

    void MappingRenderOptions::VisualReferencePointAirfields(const std::set<int> airfields)
    {
        this->visualReferencePointAirfields = airfields;
    }
} // namespace UKControllerPlugin::Mapping
