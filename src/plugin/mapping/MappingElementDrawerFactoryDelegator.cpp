#include "MappingElementDrawerFactoryDelegator.h"

namespace UKControllerPlugin::Mapping {

    MappingElementDrawerFactoryDelegator::MappingElementDrawerFactoryDelegator(
        std::map<std::string, std::shared_ptr<MappingElementDrawerFactory>> factories)
        : factories(std::move(factories))
    {
    }

    auto MappingElementDrawerFactoryDelegator::Make(const nlohmann::json& data) const
        -> std::shared_ptr<MappingElementDrawer>
    {
        const auto type = data.contains("type") ? data.at("type").get<std::string>() : std::string();
        if (!factories.contains(type)) {
            throw std::exception(std::string("Unknown mapping element type, cannot make drawer: " + type).c_str());
        }

        return factories.at(type)->Make(data);
    }
} // namespace UKControllerPlugin::Mapping
