#include "ScreenObjectInterface.h"

namespace UKControllerPlugin::RadarScreen {

    ScreenObjectInterface::~ScreenObjectInterface() = default;

    void ScreenObjectInterface::LeftClick(
        Euroscope::EuroscopeRadarLoopbackInterface& radarScreen, const std::string& description, POINT mousePosition)
    {
    }

    void ScreenObjectInterface::RightClick(
        Euroscope::EuroscopeRadarLoopbackInterface& radarScreen, const std::string& objectDescription)
    {
    }

    void ScreenObjectInterface::Drag(const std::string& objectDescription, RECT position)
    {
    }
} // namespace UKControllerPlugin::RadarScreen
