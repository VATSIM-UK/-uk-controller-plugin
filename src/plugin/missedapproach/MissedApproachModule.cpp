#include "MissedApproachAudioAlert.h"
#include "MissedApproachButton.h"
#include "MissedApproachCollection.h"
#include "MissedApproachModule.h"
#include "MissedApproachOptions.h"
#include "MissedApproachRenderOptions.h"
#include "MissedApproachRenderer.h"
#include "MissedApproachUserSettingHandler.h"
#include "NewMissedApproachPushEventHandler.h"
#include "RemoveExpiredMissedApproaches.h"
#include "ToggleMissedApproachButton.h"
#include "TriggerMissedApproach.h"
#include "bootstrap/PersistenceContainer.h"
#include "euroscope/AsrEventHandlerCollection.h"
#include "euroscope/CallbackFunction.h"
#include "euroscope/UserSettingAwareCollection.h"
#include "plugin/FunctionCallEventHandler.h"
#include "plugin/UKPlugin.h"
#include "push/PushEventProcessorCollection.h"
#include "radarscreen/ConfigurableDisplayCollection.h"
#include "timedevent/TimedEventCollection.h"

using UKControllerPlugin::Euroscope::CallbackFunction;
using UKControllerPlugin::Tag::TagFunction;

namespace UKControllerPlugin::MissedApproach {

    const int REMOVE_APPROACHES_FREQUENCY = 30;
    const int TRIGGER_MISSED_APPROACH_TAG_FUNCTION_ID = 9020;
    std::shared_ptr<MissedApproachCollection> collection;             // NOLINT
    std::shared_ptr<MissedApproachAudioAlert> audioAlert;             // NOLINT
    std::shared_ptr<MissedApproachOptions> options;                   // NOLINT
    std::shared_ptr<MissedApproachUserSettingHandler> optionsHandler; // NOLINT
    std::shared_ptr<TriggerMissedApproach> triggerHandler;            // NOLINT

    void BootstrapPlugin(const Bootstrap::PersistenceContainer& container)
    {
        // Global (not per-ASR) options
        options = std::make_shared<MissedApproachOptions>();
        optionsHandler = std::make_shared<MissedApproachUserSettingHandler>(
            options, *container.userSettingHandlers, *container.pluginUserSettingHandler);
        container.userSettingHandlers->RegisterHandler(optionsHandler);

        // The audio alerting service
        audioAlert = std::make_shared<MissedApproachAudioAlert>(
            options, *container.plugin, *container.airfieldOwnership, *container.windows);

        // The collectioh of missed approaches
        collection = std::make_shared<MissedApproachCollection>();
        container.timedHandler->RegisterEvent(
            std::make_shared<RemoveExpiredMissedApproaches>(collection), REMOVE_APPROACHES_FREQUENCY);
        container.pushEventProcessors->AddProcessor(
            std::make_shared<NewMissedApproachPushEventHandler>(collection, audioAlert));

        // Trigger missed approach
        const auto trigger = std::make_shared<TriggerMissedApproach>(
            collection, *container.windows, *container.api, *container.airfieldOwnership, audioAlert);
        triggerHandler = trigger;
        TagFunction triggerMissedApproachTagFunction(
            TRIGGER_MISSED_APPROACH_TAG_FUNCTION_ID,
            "Trigger Missed Approach",
            [trigger](
                UKControllerPlugin::Euroscope::EuroScopeCFlightPlanInterface& fp,
                UKControllerPlugin::Euroscope::EuroScopeCRadarTargetInterface& rt,
                const std::string& context,
                const POINT& mousePos) { trigger->Trigger(fp, rt); });
        container.pluginFunctionHandlers->RegisterFunctionCall(triggerMissedApproachTagFunction);
    }

    void BootstrapRadarScreen(
        const Bootstrap::PersistenceContainer& persistence,
        RadarScreen::RadarRenderableCollection& radarRenderables,
        RadarScreen::ConfigurableDisplayCollection& configurables,
        Euroscope::AsrEventHandlerCollection& asrHandlers)
    {
        // Alerts
        auto renderOptions = std::make_shared<MissedApproachRenderOptions>();
        asrHandlers.RegisterHandler(renderOptions);

        auto renderer = std::make_shared<MissedApproachRenderer>(
            collection, *persistence.airfieldOwnership, *persistence.plugin, renderOptions);
        radarRenderables.RegisterRenderer(
            radarRenderables.ReserveRendererIdentifier(), renderer, RadarScreen::RadarRenderableCollection::afterTags);

        // The button
        const auto buttonRendererId = radarRenderables.ReserveRendererIdentifier();
        const auto buttonScreenObject = radarRenderables.ReserveScreenObjectIdentifier(buttonRendererId);
        auto button = std::make_shared<MissedApproachButton>(
            collection, triggerHandler, *persistence.plugin, *persistence.airfieldOwnership, buttonScreenObject);

        radarRenderables.RegisterRenderer(buttonRendererId, button, RadarScreen::RadarRenderableCollection::afterLists);
        asrHandlers.RegisterHandler(button);

        // Button toggle
        const auto callbackId = persistence.pluginFunctionHandlers->ReserveNextDynamicFunctionId();
        const auto buttonToggle = std::make_shared<ToggleMissedApproachButton>(button, callbackId);
        configurables.RegisterDisplay(buttonToggle);
        CallbackFunction toggleButtonCallback(
            callbackId, "Trigger Missed Approach", [buttonToggle](int id, const std::string& context, const RECT& pos) {
                buttonToggle->Configure(id, context, pos);
            });
        persistence.pluginFunctionHandlers->RegisterFunctionCall(toggleButtonCallback);
    }
} // namespace UKControllerPlugin::MissedApproach
