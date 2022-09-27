#include "ToggleMappingOptionsRender.h"
#include "MappingRenderOptions.h"
#include "components/ClickableArea.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Mapping {

    ToggleMappingOptionsRender::ToggleMappingOptionsRender(
        std::shared_ptr<MappingRenderOptions> mappingOptions, int screenObjectId)
        : mappingOptions(mappingOptions), screenObjectId(screenObjectId), renderArea(0, 0, WIDTH, HEIGHT),
          backgroundBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(11, 65, 54))),
          textBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(0, 255, 0))),
          clickspot(Components::ClickableArea::Create(renderArea, this->screenObjectId, "mapToggle", false))
    {
        assert(mappingOptions && "Mapping options not set in ToggleMappingOptionsRender");
    }

    bool ToggleMappingOptionsRender::IsVisible() const
    {
        return true;
    }

    void ToggleMappingOptionsRender::LeftClick(
        Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
        int objectId,
        const std::string& objectDescription,
        POINT mousePos,
        RECT itemArea)
    {
        mappingOptions->ShowOptions(!mappingOptions->ShowOptions());
    }

    void ToggleMappingOptionsRender::Render(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        // Translate it next to the OP button
        const auto viewport = radarScreen.GetRadarViewport();
        graphics.Translated(viewport.right - 25 - WIDTH, viewport.bottom - HEIGHT, [this, &graphics, &radarScreen]() {
            graphics.FillRect(renderArea, *backgroundBrush);
            graphics.DrawString(L"MAP", renderArea, *this->textBrush);
            clickspot->Apply(graphics, radarScreen);
        });
    }
} // namespace UKControllerPlugin::Mapping
