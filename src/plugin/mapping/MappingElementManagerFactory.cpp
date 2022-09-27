#include "MappingElement.h"
#include "MappingElementFactory.h"
#include "MappingElementManager.h"
#include "MappingElementManagerFactory.h"
#include "dependency/DependencyLoaderInterface.h"

namespace UKControllerPlugin::Mapping {

    auto MakeMappingElementManager(
        MappingElementFactory& elementFactory, Dependency::DependencyLoaderInterface& dependencyLoader)
        -> std::shared_ptr<MappingElementManager>
    {
        auto mapper = std::make_unique<MappingElementManager>();
        const auto& dependency =
            dependencyLoader.LoadDependency("DEPENDENCY_MAPPING_ELEMENTS", nlohmann::json::array());
        if (!dependency.is_array()) {
            LogError("Mapping elements dependency is not an array");
            return mapper;
        }

        for (const auto& elementData : dependency) {
            const auto element = elementFactory.Make(elementData);
            if (!element) {
                LogError("Invalid mapping element " + elementData.dump());
                continue;
            }

            mapper->Add(element);
        }

        LogInfo("Loaded " + std::to_string(mapper->Count()) + " mapping elements");
        return mapper;
    }
} // namespace UKControllerPlugin::Mapping
