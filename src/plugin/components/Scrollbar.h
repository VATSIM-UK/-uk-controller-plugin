#pragma once

namespace UKControllerPlugin {
    namespace Euroscope {
        class EuroscopeRadarLoopbackInterface;
    } // namespace Euroscope
    namespace Windows {
        class GdiGraphicsInterface;
    } // namespace Windows
} // namespace UKControllerPlugin

namespace UKControllerPlugin::Components {

    class ScrollbarClickspot;
    class ScrollbarOptions;

    /**
     * A scrollbar
     */
    class Scrollbar : public std::enable_shared_from_this<Scrollbar>
    {
        public:
        Scrollbar(
            Gdiplus::Rect area,
            std::shared_ptr<ScrollbarOptions> options,
            bool isHorizontal,
            std::shared_ptr<ScrollbarClickspot> decrementClickspot,
            std::shared_ptr<ScrollbarClickspot> incrementClickspot);
        void Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen);
        [[nodiscard]] auto IncrementClickspot() const -> std::shared_ptr<ScrollbarClickspot>;
        [[nodiscard]] auto DecrementClickspot() const -> std::shared_ptr<ScrollbarClickspot>;

        private:
        // Area to use
        Gdiplus::Rect area;

        // Number of notches
        std::shared_ptr<ScrollbarOptions> options;

        // Are we a horizonal scrollbar
        const bool isHorizontal;

        // The clickspot for decrementing
        std::shared_ptr<ScrollbarClickspot> decrementClickspot;

        // The clickspot for incrementing
        std::shared_ptr<ScrollbarClickspot> incrementClickspot;

        // Brush
        std::shared_ptr<Gdiplus::Brush> backgroundBrush;
        std::shared_ptr<Gdiplus::Brush> progressBarBrush;
    };

} // namespace UKControllerPlugin::Components
