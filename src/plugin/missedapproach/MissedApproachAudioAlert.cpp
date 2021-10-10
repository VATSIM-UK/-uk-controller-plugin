#include "MissedApproach.h"
#include "MissedApproachAudioAlert.h"
#include "MissedApproachOptions.h"
#include "euroscope/EuroScopeCFlightPlanInterface.h"
#include "euroscope/EuroscopePluginLoopbackInterface.h"
#include "ownership/AirfieldServiceProviderCollection.h"
#include "windows/WinApiInterface.h"

namespace UKControllerPlugin::MissedApproach {

    MissedApproachAudioAlert::MissedApproachAudioAlert(
        std::shared_ptr<const MissedApproachOptions> options,
        Euroscope::EuroscopePluginLoopbackInterface& plugin,
        const Ownership::AirfieldServiceProviderCollection& airfieldServiceProvisions,
        Windows::WinApiInterface& winApi)
        : options(std::move(options)), plugin(plugin), airfieldServiceProvisions(airfieldServiceProvisions),
          winApi(winApi)
    {
    }

    void MissedApproachAudioAlert::Play(const std::shared_ptr<class MissedApproach>& missedApproach) const
    {
        if (!this->ShouldPlay(missedApproach)) {
            LogDebug("Skipping missed approach audio alert for " + missedApproach->Callsign());
            return;
        }

        LogInfo("Playing missed approach audio alert");
        this->winApi.PlayWave(MAKEINTRESOURCE(WAVE_MISSED_APPROACH)); // NOLINT
    }

    /**
     * Audio alerts should only be played if:
     *
     * 1. The user has elected to receive alerts for approaches created by them OR it the approach was not created by
     * them.
     * 2. The flightplan exists.
     * 3. The user is providing a specified service at the aircrafts destination airfield.
     * @param missedApproach
     * @return
     */
    auto MissedApproachAudioAlert::ShouldPlay(const std::shared_ptr<class MissedApproach>& missedApproach) const -> bool
    {
        if (!this->options->AudioAlertForCurrentUser() && missedApproach->CreatedByUser()) {
            return false;
        }

        const auto flightplan = this->plugin.GetFlightplanForCallsign(missedApproach->Callsign());
        if (!flightplan) {
            return false;
        }

        const auto airfields = this->airfieldServiceProvisions.GetAirfieldsWhereUserProvidingServices(
            this->options->AudioAlertServiceProvisions());

        return std::find(airfields.cbegin(), airfields.cend(), flightplan->GetDestination()) != airfields.cend();
    }
} // namespace UKControllerPlugin::MissedApproach
