#include "MappingElementInterface.h"
#include "MappingElementManager.h"
#include "MappingRenderer.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Mapping {
    MappingRenderer::MappingRenderer(std::shared_ptr<MappingElementManager> elementManager)
        : elementManager(elementManager)
    {
    }

    auto MappingRenderer::IsVisible() const -> bool
    {
        return true;
    }

    void MappingRenderer::Render(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        elementManager->ForEachActiveElement(
            [&graphics, &radarScreen](MappingElementInterface& element) { element.Draw(graphics, radarScreen); });
    }
} // namespace UKControllerPlugin::Mapping
