#include "MappingOptionsRenderer.h"
#include "MappingRenderOptions.h"
#include "components/Checkbox.h"
#include "components/ClickableArea.h"
#include "components/Scrollbar.h"
#include "components/ScrollbarFactory.h"
#include "components/Title.h"
#include "components/TitleBar.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Mapping {

    MappingOptionsRenderer::MappingOptionsRenderer(
        std::shared_ptr<MappingRenderOptions> mappingOptions,
        std::shared_ptr<Components::Checkbox> vrpCheckbox,
        const Components::ScrollbarFactory& scrollbarFactory)
        : mappingOptions(mappingOptions), vrpCheckbox(vrpCheckbox),
          vrpScrollbar(scrollbarFactory.MakeHorizontal({10, 400, 25, 300}, 10)),
          backgroundBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(170, 64, 64, 64)))
    {
        assert(mappingOptions && "Mapping render options not set");
        assert(vrpScrollbar && "VRP Scrollbar Not Set");
    }

    auto MappingOptionsRenderer::IsVisible() const -> bool
    {
        return mappingOptions->ShowOptions();
    }

    void MappingOptionsRenderer::LeftClick(
        Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
        int objectId,
        const std::string& objectDescription,
        POINT mousePos,
        RECT itemArea)
    {
        if (objectDescription == DISPLAY_VRP_CHECKBOX) {
            mappingOptions->ShowVisualReferencePoints(!mappingOptions->ShowVisualReferencePoints());
            return;
        }
    }

    void MappingOptionsRenderer::Render(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        graphics.Translated(50, 50, [&graphics, &radarScreen, this]() {
            const auto viewport = radarScreen.GetRadarViewport();

            // Background
            const auto width = viewport.right - viewport.left - 100;
            Gdiplus::Rect backgroundRect{0, 0, width, viewport.bottom - viewport.top - 100};
            graphics.FillRect(backgroundRect, *backgroundBrush);
            Components::ClickableArea::Create(backgroundRect, -9999, "", false)->Apply(graphics, radarScreen);

            // Titlebar
            Components::TitleBar::Create(L"Mapping Options", Gdiplus::Rect{0, 0, width, 25})
                ->WithDefaultBackgroundBrush()
                ->WithDefaultTextBrush()
                ->Draw(graphics, radarScreen);

            // VRPs
            Components::Title::Create(L"Visual Reference Points", Gdiplus::Rect{10, 35, 300, 25})->Draw(graphics);
            vrpCheckbox->WithPosition({10, 85})->Draw(graphics, radarScreen);

            vrpScrollbar->Draw(graphics, radarScreen);
        });
    }
} // namespace UKControllerPlugin::Mapping
