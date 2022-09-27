#pragma once
#include "euroscope/AsrEventHandlerInterface.h"

namespace UKControllerPlugin::Airfield {
    class AirfieldCollection;
} // namespace UKControllerPlugin::Airfield

namespace UKControllerPlugin::Mapping {
    class MappingElementManager;
    class MappingRenderOptions;

    /**
     * Loads the mapping rendering options from the ASR
     */
    class MappingRenderOptionsAsrLoader : public Euroscope::AsrEventHandlerInterface
    {
        public:
        MappingRenderOptionsAsrLoader(
            MappingElementManager& elementManager,
            std::shared_ptr<MappingRenderOptions> options,
            const Airfield::AirfieldCollection& airfields);
        void AsrLoadedEvent(Euroscope::UserSetting& userSetting) override;
        void AsrClosingEvent(Euroscope::UserSetting& userSetting) override;

        private:
        // Manages mapping elements
        MappingElementManager& elementManager;

        // Render options for mapping elements
        std::shared_ptr<MappingRenderOptions> options;

        // Airfields for checking if display is valid
        const Airfield::AirfieldCollection& airfields;

        const std::string DISPLAY_VRPS_KEY = "displayVisualReferencePoints";
        const std::string DISPLAY_VRPS_DESCRIPTION = "Display Visual Reference Point";
        const std::string AIRFIELDS_VRPS_KEY = "visualReferencePointAirfields";
        const std::string AIRFIELDS_VRPS_DESCRIPTION = "Visual Reference Point Display Airfields";
    };
} // namespace UKControllerPlugin::Mapping
