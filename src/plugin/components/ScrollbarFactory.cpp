#include "Scrollbar.h"
#include "ScrollbarClickspot.h"
#include "ScrollbarFactory.h"
#include "ScrollbarOptions.h"
#include "radarscreen/RadarRenderableCollection.h"

namespace UKControllerPlugin::Components {

    ScrollbarFactory::ScrollbarFactory(RadarScreen::RadarRenderableCollection& radarRenderables)
        : radarRenderables(radarRenderables)
    {
    }
    auto ScrollbarFactory::MakeHorizontal(Gdiplus::Rect area, unsigned short notches) const
        -> std::shared_ptr<Scrollbar>
    {
        return Make(std::move(area), notches, true);
    }

    auto ScrollbarFactory::MakeVertical(Gdiplus::Rect area, unsigned short notches) const -> std::shared_ptr<Scrollbar>
    {
        return Make(std::move(area), notches, false);
    }

    auto ScrollbarFactory::Make(Gdiplus::Rect area, unsigned short notches, bool horizontal) const
        -> std::shared_ptr<Scrollbar>
    {
        auto options = std::make_shared<ScrollbarOptions>(notches);
        std::shared_ptr<ScrollbarClickspot> incrementClickspot = std::make_shared<ScrollbarClickspot>(
            radarRenderables.ReserveScreenObjectIdentifier(), [options]() { options->Increment(); }, true);
        radarRenderables.RegisterScreenObject(incrementClickspot);

        std::shared_ptr<ScrollbarClickspot> decrementClickspot = std::make_shared<ScrollbarClickspot>(
            radarRenderables.ReserveScreenObjectIdentifier(), [options]() { options->Decrement(); }, false);
        radarRenderables.RegisterScreenObject(decrementClickspot);

        return std::make_shared<Scrollbar>(area, options, horizontal, decrementClickspot, incrementClickspot);
    }
} // namespace UKControllerPlugin::Components
