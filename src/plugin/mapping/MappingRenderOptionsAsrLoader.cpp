#include "MappingElementManager.h"
#include "MappingRenderOptions.h"
#include "MappingRenderOptionsAsrLoader.h"
#include "airfield/AirfieldCollection.h"
#include "euroscope/UserSetting.h"
#include "helper/HelperFunctions.h"

namespace UKControllerPlugin::Mapping {

    MappingRenderOptionsAsrLoader::MappingRenderOptionsAsrLoader(
        MappingElementManager& elementManager,
        std::shared_ptr<MappingRenderOptions> options,
        const Airfield::AirfieldCollection& airfields)
        : elementManager(elementManager), options(options), airfields(airfields)
    {
        assert(options && "render options not set in MappingRenderOptionsAsrLoader");
    }

    void MappingRenderOptionsAsrLoader::AsrLoadedEvent(Euroscope::UserSetting& userSetting)
    {
        // VRP display
        options->ShowVisualReferencePoints(userSetting.GetBooleanEntry(DISPLAY_VRPS_KEY, false));

        // VRP selected airfields
        std::set<int> vrpAirfields;
        for (const auto& airfield : userSetting.GetStringListEntry(AIRFIELDS_VRPS_KEY, {})) {
            if (!HelperFunctions::IsAnInteger(airfield) || airfields.FetchById(std::stoi(airfield)) == nullptr) {
                LogWarning("Invalid VRP airfield in ASR: " + airfield);
                continue;
            }

            vrpAirfields.insert(std::stoi(airfield));
        }
        options->VisualReferencePointAirfields(vrpAirfields);

        // Trigger active element refresh
        elementManager.RefreshActiveElements();
    }

    void MappingRenderOptionsAsrLoader::AsrClosingEvent(Euroscope::UserSetting& userSetting)
    {
        userSetting.Save(DISPLAY_VRPS_KEY, DISPLAY_VRPS_DESCRIPTION, options->ShowVisualReferencePoints());

        std::vector<std::string> airfieldList;
        for (const auto& airfield : options->VisualReferencePointAirfields()) {
            airfieldList.push_back(std::to_string(airfield));
        }
        userSetting.Save(AIRFIELDS_VRPS_KEY, AIRFIELDS_VRPS_DESCRIPTION, airfieldList);
    }
} // namespace UKControllerPlugin::Mapping
