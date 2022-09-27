#pragma once
#include "radarscreen/RadarRenderableCollection.h"

namespace UKControllerPlugin::Components {
    class Scrollbar;

    /**
     * Creates scrollbars
     */
    class ScrollbarFactory
    {
        public:
        ScrollbarFactory(RadarScreen::RadarRenderableCollection& radarRenderables);
        [[nodiscard]] auto MakeVertical(Gdiplus::Rect area, unsigned short notches) const -> std::shared_ptr<Scrollbar>;
        [[nodiscard]] auto MakeHorizontal(Gdiplus::Rect area, unsigned short notches) const
            -> std::shared_ptr<Scrollbar>;

        private:
        [[nodiscard]] auto Make(Gdiplus::Rect area, unsigned short notches, bool horizontal) const
            -> std::shared_ptr<Scrollbar>;

        // Radar renderables
        RadarScreen::RadarRenderableCollection& radarRenderables;
    };

} // namespace UKControllerPlugin::Components
