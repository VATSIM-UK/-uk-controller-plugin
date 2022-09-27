#pragma once
#include "MappingElementDrawerFactory.h"

namespace UKControllerPlugin::Mapping {

    /**
     * Delegates the responsibility for creating drawers to other factories.
     */
    class MappingElementDrawerFactoryDelegator : public MappingElementDrawerFactory
    {
        public:
        MappingElementDrawerFactoryDelegator(
            std::map<std::string, std::shared_ptr<MappingElementDrawerFactory>> factories);
        [[nodiscard]] auto Make(const nlohmann::json& data) const -> std::shared_ptr<MappingElementDrawer>;

        private:
        // All the factories
        const std::map<std::string, std::shared_ptr<MappingElementDrawerFactory>> factories;
    };
} // namespace UKControllerPlugin::Mapping
