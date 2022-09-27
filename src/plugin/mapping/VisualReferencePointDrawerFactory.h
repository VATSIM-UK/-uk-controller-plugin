#pragma once
#include "mapping/MappingElementDrawerFactory.h"

namespace UKControllerPlugin::Mapping {
    /**
     * Builds visual reference point drawers.
     */
    class VisualReferencePointDrawerFactory : public MappingElementDrawerFactory
    {
        public:
        [[nodiscard]] auto Make(const nlohmann::json& data) const -> std::shared_ptr<MappingElementDrawer> override;

        private:
        [[nodiscard]] auto DataValid(const nlohmann::json& data) const -> bool;
    };
} // namespace UKControllerPlugin::Mapping
