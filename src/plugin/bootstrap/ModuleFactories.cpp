#include "ModuleFactories.h"
#include "approach/ApproachModuleFactory.h"
#include "mapping/MappingModuleFactory.h"

namespace UKControllerPlugin::Bootstrap {

    ModuleFactories::ModuleFactories() = default;
    ModuleFactories::~ModuleFactories() = default;

    auto ModuleFactories::Approach() -> Approach::ApproachModuleFactory&
    {
        if (!approach) {
            approach = std::make_unique<Approach::ApproachModuleFactory>();
        }

        return *approach;
    }

    auto ModuleFactories::Mapping() -> Mapping::MappingModuleFactory&
    {
        if (!mapping) {
            mapping = std::make_unique<Mapping::MappingModuleFactory>();
        }

        return *mapping;
    }
} // namespace UKControllerPlugin::Bootstrap
