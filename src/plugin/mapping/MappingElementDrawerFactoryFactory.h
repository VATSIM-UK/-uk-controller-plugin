#pragma once

namespace UKControllerPlugin::Mapping {
    class MappingElementDrawerFactory;

    [[nodiscard]] auto MakeDrawerFactory() -> std::shared_ptr<MappingElementDrawerFactory>;
} // namespace UKControllerPlugin::Mapping
