#pragma once
#include "radarscreen/RadarRenderableInterface.h"

namespace UKControllerPlugin::Components {
    class Checkbox;
    class Scrollbar;
    class ScrollbarFactory;
} // namespace UKControllerPlugin::Components

namespace UKControllerPlugin::Mapping {
    class MappingRenderOptions;

    /**
     * Renders the mapping options to the screen
     */
    class MappingOptionsRenderer : public RadarScreen::RadarRenderableInterface
    {
        public:
        MappingOptionsRenderer(
            std::shared_ptr<MappingRenderOptions> mappingOptions,
            std::shared_ptr<Components::Checkbox> vrpCheckbox,
            const Components::ScrollbarFactory& scrollbarFactory);
        [[nodiscard]] auto IsVisible() const -> bool override;
        void LeftClick(
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
            int objectId,
            const std::string& objectDescription,
            POINT mousePos,
            RECT itemArea) override;
        void Render(
            Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) override;

        private:
        // The options
        std::shared_ptr<MappingRenderOptions> mappingOptions;

        // Checkbox for whether to display VRPs
        std::shared_ptr<Components::Checkbox> vrpCheckbox;

        // Scrollbar for VRPs
        std::shared_ptr<Components::Scrollbar> vrpScrollbar;

        // Brushes
        std::shared_ptr<Gdiplus::Brush> backgroundBrush;

        // Screen objects
        const std::string DISPLAY_VRP_CHECKBOX = "displayVrps";
    };
} // namespace UKControllerPlugin::Mapping
