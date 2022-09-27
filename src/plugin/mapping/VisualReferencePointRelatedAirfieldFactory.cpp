#include "RelatedAirfield.h"
#include "VisualReferencePointRelatedAirfieldFactory.h"
#include "VisualReferencePointRelatedAirfieldProvider.h"

namespace UKControllerPlugin::Mapping {

    VisualReferencePointRelatedAirfieldFactory::VisualReferencePointRelatedAirfieldFactory(
        std::shared_ptr<MappingRenderOptions> renderOptions)
        : renderOptions(renderOptions)
    {
    }

    auto VisualReferencePointRelatedAirfieldFactory::Make(const std::string& elementType, const nlohmann::json& data)
        -> std::shared_ptr<DisplayRule>
    {
        if (HasInvalidAirfields(data)) {
            throw std::invalid_argument("Invalid airfields in VRP related airfield factory");
        }
        return std::make_shared<RelatedAirfield>(
            std::make_shared<VisualReferencePointRelatedAirfieldProvider>(renderOptions),
            data.at("airfields").get<std::set<int>>());
    }

    auto VisualReferencePointRelatedAirfieldFactory::HasInvalidAirfields(const nlohmann::json& data) const -> bool
    {
        return data.is_array() && std::find_if_not(data.begin(), data.end(), [](const nlohmann::json& airfield) {
                                      return airfield.is_number_integer();
                                  }) == data.cend();
    }
} // namespace UKControllerPlugin::Mapping
