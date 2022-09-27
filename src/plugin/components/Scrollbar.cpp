#include "Scrollbar.h"
#include "ScrollbarClickspot.h"
#include "ScrollbarOptions.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Components {

    Scrollbar::Scrollbar(
        Gdiplus::Rect area,
        std::shared_ptr<ScrollbarOptions> options,
        bool isHorizontal,
        std::shared_ptr<ScrollbarClickspot> decrementClickspot,
        std::shared_ptr<ScrollbarClickspot> incrementClickspot)
        : area(area), options(options), isHorizontal(isHorizontal), decrementClickspot(decrementClickspot),
          incrementClickspot(incrementClickspot), backgroundBrush(std::make_shared<Gdiplus::HatchBrush>(
                                                      Gdiplus::HatchStyle::HatchStyle25Percent,
                                                      Gdiplus::Color(255, 255, 255),
                                                      Gdiplus::Color(200, 64, 64, 64))),
          progressBarBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(64, 64, 64)))
    {
        assert(options && "scrollbar options not set in scrollbar");
        assert(decrementClickspot && "decrement clickspot not set in scrollbar");
        assert(incrementClickspot && "increment clickspot not set in scrollbar");
    }

    void
    Scrollbar::Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        auto yTranslate = isHorizontal ? area.GetTop() + area.Width : area.GetTop();
        graphics.Translated(area.GetLeft(), yTranslate, [&graphics, this, &radarScreen] {
            graphics.Rotated(Gdiplus::REAL(isHorizontal ? -90 : 0), [&graphics, this, &radarScreen] {
                graphics.FillRect(Gdiplus::Rect{0, 0, area.Width, area.Height}, *backgroundBrush);
                graphics.Translated(0, area.Width * options->Notch(), [&graphics, this]() {
                    graphics.FillRect(
                        Gdiplus::Rect{
                            0,
                            0,
                            area.Width,
                            area.Width,
                        },
                        *progressBarBrush);
                });

                // Translated clickspots
                decrementClickspot->Draw(
                    {
                        0,
                        0,
                        area.Width,
                        area.Width,
                    },
                    graphics,
                    radarScreen);

                graphics.Translated(0, area.Height - area.Width, [this, &graphics, &radarScreen] {
                    incrementClickspot->Draw(
                        {
                            0,
                            0,
                            area.Width,
                            area.Width,
                        },
                        graphics,
                        radarScreen);
                });
            });
        });
    }

    auto Scrollbar::IncrementClickspot() const -> std::shared_ptr<ScrollbarClickspot>
    {
        return incrementClickspot;
    }

    auto Scrollbar::DecrementClickspot() const -> std::shared_ptr<ScrollbarClickspot>
    {
        return decrementClickspot;
    }
} // namespace UKControllerPlugin::Components
