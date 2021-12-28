#include "ToggleDepartureCoordinationList.h"
#include "DepartureCoordinationList.h"

namespace UKControllerPlugin::Departure {

    ToggleDepartureCoordinationList::ToggleDepartureCoordinationList(DepartureCoordinationList& list, int callbackId)
        : list(list), callbackId(callbackId)
    {
    }

    void ToggleDepartureCoordinationList::Configure(int functionId, std::string subject, RECT screenObjectArea)
    {
        this->list.ToggleVisible();
    }

    Plugin::PopupMenuItem ToggleDepartureCoordinationList::GetConfigurationMenuItem() const
    {
        return {
            "Toggle Departure Coordination List",
            "",
            this->callbackId,
            this->list.IsVisible() ? EuroScopePlugIn::POPUP_ELEMENT_CHECKED : EuroScopePlugIn::POPUP_ELEMENT_UNCHECKED,
            false,
            false};
    }
} // namespace UKControllerPlugin::Departure
