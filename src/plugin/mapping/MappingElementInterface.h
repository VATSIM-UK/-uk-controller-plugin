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
     * An element that can be drawn or otherwise represented on the
     * map.
     */
    class MappingElementInterface
    {
        public:
        virtual ~MappingElementInterface() = default;

        /**
         * The id of the element.
         */
        [[nodiscard]] virtual auto Id() const -> int = 0;

        /**
         * The type of the element to be drawn.
         */
        [[nodiscard]] virtual auto Type() const -> const std::string& = 0;

        /**
         * The label associated with the element.
         */
        [[nodiscard]] virtual auto Label() const -> const std::string& = 0;

        /**
         * Should we be displaying the mapping element
         */
        [[nodiscard]] virtual auto ShouldDisplay() const -> bool = 0;

        /**
         * Draw the mapping element. The area is centered on the centre of the element.
         */
        virtual void
        Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) = 0;
    };
} // namespace UKControllerPlugin::Mapping
