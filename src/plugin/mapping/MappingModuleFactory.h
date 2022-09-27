#pragma once

namespace UKControllerPlugin::Dependency {
    class DependencyLoaderInterface;
} // namespace UKControllerPlugin::Dependency

namespace UKControllerPlugin::Mapping {
    class MappingElementManager;
    class VisualReferencePoint;

    /**
     * Bootstraps up the mapping module
     */
    class MappingModuleFactory
    {
        public:
        MappingModuleFactory();
        ~MappingModuleFactory();
    };
} // namespace UKControllerPlugin::Mapping
