#pragma once
#include "MappingElementDrawer.h"

namespace UKControllerPlugin::Mapping {
    /**
     * Draws a visual reference point.
     */
    class VisualReferencePoint : public MappingElementDrawer
    {
        public:
        VisualReferencePoint(std::string label, EuroScopePlugIn::CPosition position);
        void
        Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) override;
        [[nodiscard]] auto Label() const -> const std::string&;
        [[nodiscard]] auto Position() const -> const EuroScopePlugIn::CPosition&;

        private:
        // The label for the VRP
        std::string label;

        // Where on the map to draw
        EuroScopePlugIn::CPosition position;

        // A pen for drawing
        std::shared_ptr<Gdiplus::Pen> pen;

        // Text brush
        std::shared_ptr<Gdiplus::Brush> textBrush;
    };
} // namespace UKControllerPlugin::Mapping
