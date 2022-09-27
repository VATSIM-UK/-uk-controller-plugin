#pragma once

namespace UKControllerPlugin::Mapping {
    class MappingElementDrawer;

    class MappingElementDrawerFactory
    {
        public:
        virtual ~MappingElementDrawerFactory() = default;
        [[nodiscard]] virtual auto Make(const nlohmann::json& data) const -> std::shared_ptr<MappingElementDrawer> = 0;
    };
} // namespace UKControllerPlugin::Mapping
