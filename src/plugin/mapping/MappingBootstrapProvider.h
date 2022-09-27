#pragma once
#include "bootstrap/BootstrapProviderInterface.h"

namespace UKControllerPlugin::Mapping {
    /**
     * Bootstraps the mapping module
     */
    class MappingBootstrapProvider : public Bootstrap::BootstrapProviderInterface
    {
        public:
        void BootstrapRadarScreen(
            const Bootstrap::PersistenceContainer& container,
            RadarScreen::RadarRenderableCollection& radarRenderables,
            RadarScreen::ConfigurableDisplayCollection& configurables,
            Euroscope::AsrEventHandlerCollection& asrHandlers,
            const RadarScreen::MenuToggleableDisplayFactory& toggleableDisplayFactory) override;
    };
} // namespace UKControllerPlugin::Mapping
