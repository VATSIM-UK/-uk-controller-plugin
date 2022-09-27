#include "Checkbox.h"
#include "CheckboxProviderInterface.h"
#include "ClickableArea.h"
#include "graphics/FontManager.h"
#include "graphics/GdiGraphicsInterface.h"
#include "graphics/StringFormatManager.h"
#include "helper/HelperFunctions.h"

namespace UKControllerPlugin::Components {

    Checkbox::Checkbox(std::shared_ptr<CheckboxProviderInterface> provider, int screenObjectId)
        : provider(provider), screenObjectId(screenObjectId),
          pen(std::make_shared<Gdiplus::Pen>(Gdiplus::Color(255, 255, 255))),
          brush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(255, 255, 255))),
          clickableArea(ClickableArea::Create(
              Gdiplus::Rect(area.GetLeft(), area.GetTop(), labelArea.GetRight() - area.GetLeft(), labelArea.Height),
              screenObjectId,
              "checkbox" + provider->Label(),
              false)),
          font(Graphics::FontManager::Instance().GetDefault()),
          stringFormat(Graphics::StringFormatManager::Instance().GetLeftAlign())
    {
    }

    auto Checkbox::Create(std::shared_ptr<CheckboxProviderInterface> provider, int screenObjectId)
        -> std::shared_ptr<Checkbox>
    {
        return std::shared_ptr<Checkbox>(new Checkbox(provider, screenObjectId));
    }

    auto Checkbox::Checked(bool checked) -> std::shared_ptr<Checkbox>
    {
        this->checked = checked;
        return shared_from_this();
    }

    void Checkbox::Draw(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const
    {
        // Draw the border
        graphics.DrawRect(area, *pen);

        // Draw the checkmark if checked
        if (checked) {
            graphics.DrawLine(
                *pen, Gdiplus::Point{area.GetLeft(), area.GetTop()}, Gdiplus::Point{area.GetRight(), area.GetBottom()});
            graphics.DrawLine(
                *pen, Gdiplus::Point{area.GetLeft(), area.GetBottom()}, Gdiplus::Point{area.GetRight(), area.GetTop()});
        }

        // Clickspot
        clickableArea->Apply(graphics, radarScreen);

        // Label
        graphics.DrawString(
            HelperFunctions::ConvertToWideString(provider->Label()), labelArea, *brush, stringFormat, font);
    }

    void Checkbox::LeftClick(
        Euroscope::EuroscopeRadarLoopbackInterface& radarScreen, const std::string& description, POINT mousePosition)
    {
        checked = !checked;
        provider->StateChanged(checked);
    }

    auto Checkbox::WithPosition(POINT position) -> std::shared_ptr<Checkbox>
    {
        area = {position.x, position.y, DIMENSIONS, DIMENSIONS};
        labelArea = {area.GetRight() + 10, position.y, 250, DIMENSIONS};
        this->clickableArea->WithPosition(
            {area.GetLeft(), area.GetTop(), labelArea.GetRight() - area.GetLeft(), labelArea.Height});
        return shared_from_this();
    }

    auto Checkbox::ScreenObjectId() const -> int
    {
        return screenObjectId;
    }
} // namespace UKControllerPlugin::Components
