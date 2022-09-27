#pragma once

namespace UKControllerPlugin::Windows {
    class GdiGraphicsInterface;
} // namespace UKControllerPlugin::Windows

namespace UKControllerPlugin::Graphics {
    void FillTriangle(Windows::GdiGraphicsInterface& graphics, Gdiplus::Brush& brush, const Gdiplus::Rect& drawArea);
    [[nodiscard]] auto TriangleDrawDimensions() -> Gdiplus::REAL;
    [[nodiscard]] auto TriangleXScale(const Gdiplus::Rect& drawArea) -> Gdiplus::REAL;
    [[nodiscard]] auto TriangleYScale(const Gdiplus::Rect& drawArea) -> Gdiplus::REAL;
} // namespace UKControllerPlugin::Graphics
