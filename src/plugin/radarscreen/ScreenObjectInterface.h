#pragma once

namespace UKControllerPlugin::Euroscope {
    class EuroscopeRadarLoopbackInterface;
} // namespace UKControllerPlugin::Euroscope

namespace UKControllerPlugin::RadarScreen {

    /**
     * A screen object that can be clicked or dragged
     */
    class ScreenObjectInterface
    {
        public:
        virtual ~ScreenObjectInterface();

        [[nodiscard]] virtual auto ScreenObjectId() const -> int = 0;

        /*
            Called when a screen object is left clicked on.
        */
        virtual void LeftClick(
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
            const std::string& description,
            POINT mousePosition);

        /*
            Called when a screen object is right clicked on.
        */
        virtual void
        RightClick(Euroscope::EuroscopeRadarLoopbackInterface& radarScreen, const std::string& objectDescription);

        /*
            Called when an object is moved.
        */
        virtual void Drag(const std::string& objectDescription, RECT position);
    };

} // namespace UKControllerPlugin::RadarScreen
