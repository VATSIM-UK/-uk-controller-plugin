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
    class Checkbox;
    class Scrollbar;

    /**
     * Multiple checkboxes that have a scrollbar
     */
    class ScrollableCheckboxes
    {
        public:
        ScrollableCheckboxes(std::list<std::shared_ptr<Checkbox>> checkboxes, std::shared_ptr<Scrollbar> scrollbar);
        void
        Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const;

        private:
        // All the checkboxes to display
        std::list<std::shared_ptr<Checkbox>> checkboxes;

        // The scrollbar
        std::shared_ptr<Scrollbar> scrollbar;
    };

} // namespace UKControllerPlugin::Components
