#include "VisualReferencePoint.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"
#include "helper/HelperFunctions.h"
#include "geometry/RectangleFunctions.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Mapping {

    VisualReferencePoint::VisualReferencePoint(std::string label, EuroScopePlugIn::CPosition position)
        : label(label), position(std::move(position)),
          pen(std::make_shared<Gdiplus::Pen>(Gdiplus::Color(50, 127, 168))),
          textBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(255, 255, 255)))
    {
    }

    void VisualReferencePoint::Draw(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        const auto viewport = radarScreen.GetRadarViewport();
        const auto screenPosition = radarScreen.ConvertCoordinateToScreenPoint(position);

        if (!Geometry::PointInRect(screenPosition, viewport)) {
            return;
        }

        graphics.Translated(screenPosition.x, screenPosition.y, [&graphics, this]() {
            Gdiplus::Rect area{-10, -10, 20, 20};

            graphics.DrawCircle(area, *pen);
            graphics.DrawLine(*pen, Gdiplus::PointF{0, -10}, Gdiplus::PointF{0, 10});
            graphics.DrawLine(*pen, Gdiplus::PointF{-10, 0}, Gdiplus::PointF{10, 0});
            graphics.DrawString(
                HelperFunctions::ConvertToWideString(label),
                Gdiplus::Rect{-90, area.GetBottom() + 5, 180, 20},
                *textBrush);
        });
    }

    auto VisualReferencePoint::Position() const -> const EuroScopePlugIn::CPosition&
    {
        return position;
    }

    auto VisualReferencePoint::Label() const -> const std::string&
    {
        return label;
    }
} // namespace UKControllerPlugin::Mapping
