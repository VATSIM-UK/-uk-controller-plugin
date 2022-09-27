#include "VisualReferencePoint.h"
#include "VisualReferencePointDrawerFactory.h"

namespace UKControllerPlugin::Mapping {

    auto VisualReferencePointDrawerFactory::Make(const nlohmann::json& data) const
        -> std::shared_ptr<MappingElementDrawer>
    {
        if (!DataValid(data)) {
            throw std::exception("Invalid VRP data for drawer creation");
        }

        EuroScopePlugIn::CPosition position;
        position.m_Latitude = data.at("latitude").get<double>();
        position.m_Longitude = data.at("longitude").get<double>();

        return std::make_shared<VisualReferencePoint>(data.at("name").get<std::string>(), position);
    }

    auto VisualReferencePointDrawerFactory::DataValid(const nlohmann::json& data) const -> bool
    {
        return data.contains("name") && data.at("name").is_string() && data.contains("latitude") &&
               data.at("latitude").is_number() && data.contains("longitude") && data.at("longitude").is_number();
    }
} // namespace UKControllerPlugin::Mapping
