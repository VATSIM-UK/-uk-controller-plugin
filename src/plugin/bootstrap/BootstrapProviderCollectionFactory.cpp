#include "BootstrapProviderCollection.h"
#include "BootstrapProviderCollectionFactory.h"
#include "approach/ApproachBootstrapProvider.h"
#include "mapping/MappingBootstrapProvider.h"

namespace UKControllerPlugin::Bootstrap {
    auto Make() -> std::unique_ptr<BootstrapProviderCollection>
    {
        auto collection = std::make_unique<BootstrapProviderCollection>();
        collection->AddProvider(std::make_unique<Approach::ApproachBootstrapProvider>());
        collection->AddProvider(std::make_unique<Mapping::MappingBootstrapProvider>());

        return collection;
    }
} // namespace UKControllerPlugin::Bootstrap
