#include "StandardButtons.h"
#include "graphics/DrawTriangle.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Components {

    // Coordinates of the close cross
    Gdiplus::Point closeTopLeft = {-5, -5};
    Gdiplus::Point closeBottomRight = {5, 5};
    Gdiplus::Point closeBottomLeft = {-5, 5};
    Gdiplus::Point closeTopRight = {5, -5};

    // The standard button sizing
    Gdiplus::REAL buttonSize(10);

    /*
     * Draws a standard X-shaped close button of the specified colour.
     */
    auto CloseButton(Gdiplus::Color colour) -> std::function<void(Windows::GdiGraphicsInterface&, const Gdiplus::Rect&)>
    {
        auto pen = std::make_shared<Gdiplus::Pen>(colour, 2.0F);
        return [pen](Windows::GdiGraphicsInterface& graphics, const Gdiplus::Rect& drawArea) {
            Gdiplus::REAL scaleX = drawArea.Width / buttonSize;
            Gdiplus::REAL scaleY = drawArea.Height / buttonSize;
            ScalePen(pen, scaleX, scaleY);

            graphics.Translated(
                static_cast<Gdiplus::REAL>(5) * scaleX,
                static_cast<Gdiplus::REAL>(5) * scaleY,
                [&graphics, &pen, &scaleX, &scaleY] {
                    graphics.Scaled(scaleX, scaleY, [&graphics, &pen]() {
                        graphics.DrawLine(*pen, closeTopLeft, closeBottomRight);
                        graphics.DrawLine(*pen, closeBottomLeft, closeTopRight);
                    });
                });
        };
    }

    std::function<void(Windows::GdiGraphicsInterface&, const Gdiplus::Rect&)> CloseButton()
    {
        return CloseButton(Gdiplus::Color(227, 227, 227));
    }

    /*
     * Draws a standard triangle shaped collapse button of the specified colour.
     *
     * The state function tells the button whether it is collapsed or not.
     */
    std::function<void(Windows::GdiGraphicsInterface&, const Gdiplus::Rect&)>
    CollapseButton(Gdiplus::Color colour, std::function<bool()> stateFunction)
    {
        auto brush = std::make_shared<Gdiplus::SolidBrush>(colour);
        return [brush, stateFunction](Windows::GdiGraphicsInterface& graphics, const Gdiplus::Rect& drawArea) {
            graphics.Translated(
                static_cast<Gdiplus::REAL>(Graphics::TriangleDrawDimensions() / 2) * drawArea.Width /
                    Graphics::TriangleDrawDimensions(),
                static_cast<Gdiplus::REAL>(Graphics::TriangleDrawDimensions() / 2) * drawArea.Height /
                    Graphics::TriangleDrawDimensions(),
                [&graphics, &stateFunction, &brush, drawArea] {
                    graphics.Rotated(
                        stateFunction() ? static_cast<Gdiplus::REAL>(180) : static_cast<Gdiplus::REAL>(0),
                        [&graphics, &brush, drawArea]() { Graphics::FillTriangle(graphics, *brush, drawArea); });
                });
        };
    }

    std::function<void(Windows::GdiGraphicsInterface& graphics, const Gdiplus::Rect&)>
    CollapseButton(std::function<bool()> stateFunction)
    {
        return CollapseButton(Gdiplus::Color(227, 227, 227), stateFunction);
    }

    void ScalePen(const std::shared_ptr<Gdiplus::Pen>& pen, Gdiplus::REAL& scaleX, Gdiplus::REAL& scaleY)
    {
        pen->ResetTransform();
        pen->ScaleTransform(1 / scaleX, 1 / scaleY);
    }

    std::function<void(Windows::GdiGraphicsInterface&, const Gdiplus::Rect&)> DeleteButton(Gdiplus::Color colour)
    {
        return CloseButton(colour);
    }

    std::function<void(Windows::GdiGraphicsInterface&, const Gdiplus::Rect&)> DeleteButton()
    {
        return CloseButton();
    }

    std::function<void(Windows::GdiGraphicsInterface&, const Gdiplus::Rect&)> UpArrow(Gdiplus::Color colour)
    {
        return CollapseButton(colour, []() { return false; });
    }

    std::function<void(Windows::GdiGraphicsInterface&, const Gdiplus::Rect&)> DownArrow(Gdiplus::Color colour)
    {
        return CollapseButton(colour, []() { return true; });
    }
} // namespace UKControllerPlugin::Components
