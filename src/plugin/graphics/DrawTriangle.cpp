#include "DrawTriangle.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Graphics {

    // Coordinates of the triangle
    Gdiplus::Point trianglePoints[3] = {Gdiplus::Point(0, -5), Gdiplus::Point(5, 5), Gdiplus::Point(-5, 5)};

    // The default draw size of a triangle
    Gdiplus::REAL triangleSize(10);

    void FillTriangle(Windows::GdiGraphicsInterface& graphics, Gdiplus::Brush& brush, const Gdiplus::Rect& drawArea)
    {
        graphics.Scaled(TriangleXScale(drawArea), TriangleYScale(drawArea), [&graphics, &brush]() {
            graphics.FillPolygon(trianglePoints, brush, 3);
        });
    }

    auto TriangleDrawDimensions() -> Gdiplus::REAL
    {
        return triangleSize;
    }

    auto TriangleXScale(const Gdiplus::Rect& drawArea) -> Gdiplus::REAL
    {
        return drawArea.Width / TriangleDrawDimensions();
    }

    auto TriangleYScale(const Gdiplus::Rect& drawArea) -> Gdiplus::REAL
    {
        return drawArea.Height / TriangleDrawDimensions();
    }
} // namespace UKControllerPlugin::Graphics
