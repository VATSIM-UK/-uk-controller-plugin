#pragma once
#include "radarscreen/RadarRenderableInterface.h"

namespace UKControllerPlugin::Components {
    class ClickableArea;
} // namespace UKControllerPlugin::Components

namespace UKControllerPlugin::Mapping {
    class MappingRenderOptions;

    class ToggleMappingOptionsRender : public RadarScreen::RadarRenderableInterface
    {
        public:
        ToggleMappingOptionsRender(std::shared_ptr<MappingRenderOptions> mappingOptions, int screenObjectId);
        auto IsVisible() const -> bool override;
        void LeftClick(
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
            int objectId,
            const std::string& objectDescription,
            POINT mousePos,
            RECT itemArea) override;
        void Render(
            Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) override;

        private:
        // Rendering constants
        inline static const int WIDTH = 35;
        inline static const int HEIGHT = 25;

        // The options
        std::shared_ptr<MappingRenderOptions> mappingOptions;

        // For clickspots
        const int screenObjectId;

        // The rendering area
        const Gdiplus::Rect renderArea;

        // Background brush
        std::shared_ptr<Gdiplus::Brush> backgroundBrush;

        // Text brush
        std::shared_ptr<Gdiplus::Brush> textBrush;

        // For clicking
        std::shared_ptr<Components::ClickableArea> clickspot;
    };
} // namespace UKControllerPlugin::Mapping
