#include "pch/stdafx.h"
#include "initialaltitude/InitialAltitudeModule.h"
#include "initialaltitude/InitialAltitudeEventHandler.h"
#include "initialaltitude/InitialAltitudeGeneratorFactory.h"
#include "flightplan/FlightPlanEventHandlerCollection.h"
#include "bootstrap/PersistenceContainer.h"
#include "tag/TagFunction.h"

using UKControllerPlugin::InitialAltitude::InitialAltitudeGeneratorFactory;
using UKControllerPlugin::Bootstrap::PersistenceContainer;
using UKControllerPlugin::Dependency::DependencyCache;
using UKControllerPlugin::InitialAltitude::InitialAltitudeEventHandler;
using UKControllerPlugin::Flightplan::FlightPlanEventHandlerCollection;
using UKControllerPlugin::Tag::TagFunction;
namespace UKControllerPlugin {
    namespace InitialAltitude {

        /*
            Initialises the initial altitude module. Gets the altitudes from the dependency cache
            and registers the event handler to receive flightplan events.
        */
        void InitialAltitudeModule::BootstrapPlugin(
            DependencyCache & dependency,
            PersistenceContainer & persistence
        ) {
            persistence.initialAltitudes = InitialAltitudeGeneratorFactory::Create(dependency);
            std::shared_ptr<InitialAltitudeEventHandler> initialAltitudeEventHandler(
                new InitialAltitudeEventHandler(
                    *persistence.initialAltitudes,
                    *persistence.activeCallsigns,
                    *persistence.airfieldOwnership,
                    *persistence.login,
                    *persistence.deferredHandlers,
                    *persistence.plugin
                )
            );

            persistence.initialAltitudeEvents = initialAltitudeEventHandler;
            persistence.userSettingHandlers->RegisterHandler(initialAltitudeEventHandler);
            persistence.flightplanHandler->RegisterHandler(initialAltitudeEventHandler);


            TagFunction recycleFunction(
                InitialAltitudeModule::recycleFunctionId,
                "Recycle Initial Altitude",
                std::bind(
                    &InitialAltitudeEventHandler::RecycleInitialAltitude,
                    *initialAltitudeEventHandler,
                    std::placeholders::_1,
                    std::placeholders::_2
                )
            );
            persistence.pluginFunctionHandlers->RegisterFunctionCall(recycleFunction);
        }
    }  // namespace InitialAltitude
}  // namespace UKControllerPlugin
