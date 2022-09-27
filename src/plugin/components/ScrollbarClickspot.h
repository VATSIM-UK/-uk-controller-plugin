#pragma once
#include <string>
#include <windef.h>
#include "radarscreen/ScreenObjectInterface.h"

namespace UKControllerPlugin {
    namespace Euroscope {
        class EuroscopeRadarLoopbackInterface;
    } // namespace Euroscope
    namespace Windows {
        class GdiGraphicsInterface;
    } // namespace Windows
} // namespace UKControllerPlugin

namespace UKControllerPlugin::Components {
    class ClickableArea;

    /**
     * Clickspot for scrollbars.
     */
    class ScrollbarClickspot : public RadarScreen::ScreenObjectInterface
    {
        public:
        ScrollbarClickspot(int screenObjectId, std::function<void()> clicked, bool increments);
        void Draw(
            const Gdiplus::Rect& area,
            Windows::GdiGraphicsInterface& graphics,
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen);
        void LeftClick(
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
            const std::string& description,
            POINT mousePosition) override;
        auto ScreenObjectId() const -> int override;

        private:
        // The id of the screen object
        const int screenObjectId;

        // What to do when its clicked
        const std::function<void()> clicked;

        // Are we incrementing or decrementing (direction of arrow)
        const bool increments;

        // The actual clickspot
        std::shared_ptr<ClickableArea> clickableArea;

        // Brush
        std::shared_ptr<Gdiplus::Brush> brush;
    };
} // namespace UKControllerPlugin::Components
