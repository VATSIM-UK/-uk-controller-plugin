#include "RectangleFunctions.h"

namespace UKControllerPlugin::Geometry {
    auto PointInRect(POINT point, RECT rect) -> bool
    {
        return point.x >= rect.left && point.x <= rect.right && point.y >= rect.top && point.y <= rect.bottom;
    }
} // namespace UKControllerPlugin::Geometry
