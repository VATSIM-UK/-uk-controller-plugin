#pragma once

namespace UKControllerPlugin {
    namespace Euroscope {
        class EuroscopeRadarLoopbackInterface;
    } // namespace Euroscope
    namespace Windows {
        class GdiGraphicsInterface;
    } // namespace Windows
} // namespace UKControllerPlugin

namespace UKControllerPlugin::Mapping {

    /**
     * A class that knows how to draw a mapping element.
     */
    class MappingElementDrawer
    {
        public:
        virtual ~MappingElementDrawer() = default;

        /**
         * Draw the mapping element. The area is centered on the centre of the element.
         */
        virtual void
        Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) = 0;
    };
} // namespace UKControllerPlugin::Mapping
