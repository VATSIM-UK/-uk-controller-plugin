#pragma once

namespace UKControllerPlugin::Dependency {
    class DependencyLoaderInterface;
} // namespace UKControllerPlugin::Dependency

namespace UKControllerPlugin::Mapping {
    class MappingElementManager;
    class MappingElementFactory;

    [[nodiscard]] auto MakeMappingElementManager(
        MappingElementFactory& elementFactory, Dependency::DependencyLoaderInterface& dependencyLoader)
        -> std::shared_ptr<MappingElementManager>;
} // namespace UKControllerPlugin::Mapping
