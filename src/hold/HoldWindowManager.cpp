#include "pch/stdafx.h"
#include "hold/HoldWindowManager.h"
#include "hold/HoldDisplay.h"
#include "hold/HoldManager.h"
#include "euroscope/EuroscopePluginLoopbackInterface.h"
#include "euroscope/EuroScopeCFlightPlanInterface.h"
#include "euroscope/EuroScopeCRadarTargetInterface.h"
#include "plugin/PopupMenuItem.h"

using UKControllerPlugin::Hold::HoldManager;
using UKControllerPlugin::Euroscope::EuroscopePluginLoopbackInterface;
using UKControllerPlugin::Euroscope::EuroScopeCFlightPlanInterface;
using UKControllerPlugin::Euroscope::EuroScopeCRadarTargetInterface;
using UKControllerPlugin::Plugin::PopupMenuItem;

namespace UKControllerPlugin {
    namespace Hold {

        HoldWindowManager::HoldWindowManager(
            HWND euroscopeWindow,
            HINSTANCE dllInstance,
            const HoldManager & holdManager,
            EuroscopePluginLoopbackInterface & plugin
        )
            : euroscopeWindow(euroscopeWindow), dllInstance(dllInstance), holdManager(holdManager), plugin(plugin)
        {

        }

        /*
            Add a window.
        */
        void HoldWindowManager::AddWindow(unsigned int holdId)
        {
            const ManagedHold * managedHold = this->holdManager.GetManagedHold(holdId);

            if (!managedHold) {
                LogError("Tried to open hold display for unknown hold " + std::to_string(holdId));
                return;
            }

            //this->holdDisplays.emplace_back(euroscopeWindow, dllInstance, *managedHold);
        }

        size_t HoldWindowManager::CountDisplays(void) const
        {
            return this->holdDisplays.size();
        }

        /*
            Refresh all windows
        */
        void HoldWindowManager::RefreshWindows(void) const
        {
            for (
                std::list<HoldDisplay>::const_iterator it = this->holdDisplays.cbegin();
                it != this->holdDisplays.cend();
                ++it
            ) {
                //it->Redraw();
            }
        }

    }  // namespace Hold
}  // namespace UKControllerPlugin
