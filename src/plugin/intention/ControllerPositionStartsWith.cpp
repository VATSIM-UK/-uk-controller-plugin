#include "ControllerPositionStartsWith.h"
#include "controller/ActiveCallsign.h"
#include "controller/ActiveCallsignCollection.h"
#include "controller/ControllerPosition.h"
#include "euroscope/EuroScopeCFlightPlanInterface.h"

namespace UKControllerPlugin::IntentionCode {

    ControllerPositionStartsWith::ControllerPositionStartsWith(
        const UKControllerPlugin::Controller::ActiveCallsignCollection& activeControllers, std::string pattern)
        : activeControllers(activeControllers), pattern(std::move(pattern))
    {
    }

    auto ControllerPositionStartsWith::Passes(
        const Euroscope::EuroScopeCFlightPlanInterface& flightplan,
        const Euroscope::EuroScopeCRadarTargetInterface& radarTarget) -> bool
    {
        return activeControllers.UserHasCallsign() &&
               activeControllers.GetUserCallsign().GetNormalisedPosition().GetCallsign().substr(0, pattern.size()) ==
                   pattern;
    }

    auto ControllerPositionStartsWith::Pattern() const -> const std::string&
    {
        return pattern;
    }
} // namespace UKControllerPlugin::IntentionCode
