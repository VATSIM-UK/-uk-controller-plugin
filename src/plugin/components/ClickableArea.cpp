#include "components/ClickableArea.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Components {

    std::shared_ptr<ClickableArea>
    ClickableArea::Create(Gdiplus::Rect area, int screenObjectId, std::string screenObjectDescription, bool draggable)
    {
        return std::shared_ptr<ClickableArea>(
            new ClickableArea(area, screenObjectId, std::move(screenObjectDescription), draggable));
    }

    void ClickableArea::WithPosition(Gdiplus::Rect area)
    {
        this->area = area;
    }

    /*
     * Apply whatever transformation GDI is currently using to the clickable area, so
     * we can render the clickspot correctly on screen.
     */
    void ClickableArea::Apply(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const
    {
        std::shared_ptr<Gdiplus::Matrix> transform = graphics.GetTotalTransform();
        Gdiplus::Point points[2]{{area.GetLeft(), area.GetTop()}, {area.GetRight(), area.GetBottom()}};
        transform->TransformPoints(points, 2);

        auto pen = std::make_shared<Gdiplus::Pen>(Gdiplus::Color(255, 0, 0));
        graphics.DrawRect(area, *pen);
        radarScreen.RegisterScreenObject(
            this->screenObjectId,
            this->screenObjectDescription,
            RECT{
                static_cast<LONG>(points[0].X < points[1].X ? points[0].X : points[1].X),
                static_cast<LONG>(points[0].Y < points[1].Y ? points[0].Y : points[1].Y),
                static_cast<LONG>(points[0].X < points[1].X ? points[1].X : points[0].X),
                static_cast<LONG>(points[0].Y < points[1].Y ? points[1].Y : points[0].Y),
            },
            this->draggable);
    }

    ClickableArea::ClickableArea(
        Gdiplus::Rect area, int screenObjectId, std::string screenObjectDescription, bool draggable)
        : screenObjectDescription(std::move(screenObjectDescription)), area(area), screenObjectId(screenObjectId),
          draggable(draggable)
    {
    }
} // namespace UKControllerPlugin::Components
