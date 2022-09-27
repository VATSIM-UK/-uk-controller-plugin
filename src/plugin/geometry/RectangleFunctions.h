#pragma once

namespace UKControllerPlugin::Geometry {
    [[nodiscard]] auto PointInRect(POINT point, RECT rect) -> bool;
}
