#include "CachedAircraftFirExitGenerator.h"
#include "CachedAircraftIntentionCodeGenerator.h"
#include "FirExitPointCollection.h"
#include "FirExitPointCollectionFactory.h"
#include "IntentionCodeCollection.h"
#include "IntentionCodeCollectionFactory.h"
#include "IntentionCodeEventHandlerCollection.h"
#include "IntentionCodeModuleFactory.h"
#include "dependency/DependencyLoaderInterface.h"

namespace UKControllerPlugin::IntentionCode {

    IntentionCodeModuleFactory::IntentionCodeModuleFactory() = default;
    IntentionCodeModuleFactory::~IntentionCodeModuleFactory() = default;

    auto IntentionCodeModuleFactory::FirExitGenerator(Dependency::DependencyLoaderInterface& dependencyLoader)
        -> AircraftFirExitGenerator&
    {
        return *CachedFirExitGenerator(dependencyLoader);
    }

    auto IntentionCodeModuleFactory::ExitPointCollection(Dependency::DependencyLoaderInterface& dependencyLoader)
        -> const FirExitPointCollection&
    {
        if (!exitPoints) {
            exitPoints = MakeFirExitPointCollection(
                dependencyLoader.LoadDependency("DEPENDENCY_FIR_EXIT_POINTS", nlohmann::json::array()));
        }

        return *exitPoints;
    }

    auto IntentionCodeModuleFactory::CachedFirExitGenerator(Dependency::DependencyLoaderInterface& dependencyLoader)
        -> std::shared_ptr<CachedAircraftFirExitGenerator>
    {
        if (!firExitGenerator) {
            firExitGenerator = std::make_shared<CachedAircraftFirExitGenerator>(ExitPointCollection(dependencyLoader));
        }

        return firExitGenerator;
    }

    auto IntentionCodeModuleFactory::IntentionCodes(
        Dependency::DependencyLoaderInterface& dependencyLoader,
        const Controller::ActiveCallsignCollection& activeControllers) -> const IntentionCodeCollection&
    {
        if (!intentionCodes) {
            intentionCodes = MakeIntentionCodeCollection(
                dependencyLoader.LoadDependency("DEPENDENCY_INTENTION_CODES", nlohmann::json::array()),
                FirExitGenerator(dependencyLoader),
                activeControllers);
        }

        return *intentionCodes;
    }

    auto IntentionCodeModuleFactory::IntentionCodeEventHandlers() -> IntentionCodeEventHandlerCollection&
    {
        if (!intentionCodeEventHandlers) {
            intentionCodeEventHandlers = std::make_unique<IntentionCodeEventHandlerCollection>();
        }

        return *intentionCodeEventHandlers;
    }

    auto IntentionCodeModuleFactory::IntentionCodeGenerator(
        Dependency::DependencyLoaderInterface& dependencyLoader,
        const Controller::ActiveCallsignCollection& activeControllers) -> AircraftIntentionCodeGenerator&
    {
        return CachedIntentionCodeGenerator(dependencyLoader, activeControllers);
    }

    auto IntentionCodeModuleFactory::CachedIntentionCodeGenerator(
        Dependency::DependencyLoaderInterface& dependencyLoader,
        const Controller::ActiveCallsignCollection& activeControllers) -> CachedAircraftIntentionCodeGenerator&
    {
        if (!intentionCodeGenerator) {
            intentionCodeGenerator = std::make_unique<CachedAircraftIntentionCodeGenerator>(
                IntentionCodes(dependencyLoader, activeControllers), IntentionCodeEventHandlers());
        }

        return *intentionCodeGenerator;
    }
} // namespace UKControllerPlugin::IntentionCode
