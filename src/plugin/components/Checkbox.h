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
    class CheckboxProviderInterface;
    class ClickableArea;

    /**
     * A checkbox
     */
    class Checkbox : public std::enable_shared_from_this<Checkbox>, public RadarScreen::ScreenObjectInterface
    {
        public:
        static auto Create(std::shared_ptr<CheckboxProviderInterface> provider, int screenObjectId)
            -> std::shared_ptr<Checkbox>;
        auto Checked(bool checked) -> std::shared_ptr<Checkbox>;
        void
        Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const;
        void LeftClick(
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
            const std::string& description,
            POINT mousePosition) override;
        auto ScreenObjectId() const -> int override;
        auto WithPosition(POINT position) -> std::shared_ptr<Checkbox>;

        protected:
        Checkbox(std::shared_ptr<CheckboxProviderInterface> provider, int screenObjectId);

        private:
        // The provider
        std::shared_ptr<CheckboxProviderInterface> provider;

        // The id of the screen object
        int screenObjectId;

        // Clickspot area
        Gdiplus::Rect area;
        Gdiplus::Rect labelArea;

        // Pen
        std::shared_ptr<Gdiplus::Pen> pen;
        std::shared_ptr<Gdiplus::Brush> brush;

        // Clickspot
        std::shared_ptr<ClickableArea> clickableArea;

        // Font
        const Gdiplus::Font& font;

        // String format
        const Gdiplus::StringFormat& stringFormat;

        // Checked
        bool checked = false;

        // How big is it
        inline static const int DIMENSIONS = 15;
    };

} // namespace UKControllerPlugin::Components
