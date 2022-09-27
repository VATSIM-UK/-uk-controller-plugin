#include "DisplayRulesetFactoryFactory.h"
#include "MappingBootstrapProvider.h"
#include "MappingElementDrawerFactoryFactory.h"
#include "MappingElementFactory.h"
#include "MappingElementManager.h"
#include "MappingElementManagerFactory.h"
#include "MappingModuleFactory.h"
#include "MappingOptionsRenderer.h"
#include "MappingRenderer.h"
#include "MappingRenderOptions.h"
#include "MappingRenderOptionsAsrLoader.h"
#include "ToggleMappingOptionsRender.h"
#include "VisualReferencePointCheckboxProvider.h"
#include "bootstrap/ModuleFactories.h"
#include "bootstrap/PersistenceContainer.h"
#include "components/Checkbox.h"
#include "components/ScrollbarFactory.h"
#include "euroscope/AsrEventHandlerCollection.h"
#include "radarscreen/RadarRenderableCollection.h"

namespace UKControllerPlugin::Mapping {
    void MappingBootstrapProvider::BootstrapRadarScreen(
        const Bootstrap::PersistenceContainer& container,
        RadarScreen::RadarRenderableCollection& radarRenderables,
        RadarScreen::ConfigurableDisplayCollection& configurables,
        Euroscope::AsrEventHandlerCollection& asrHandlers,
        const RadarScreen::MenuToggleableDisplayFactory& toggleableDisplayFactory)
    {
        // The rendering options
        auto renderOptions = std::make_shared<MappingRenderOptions>();

        // Create the element manager for this radar screen
        auto elementFactory = std::make_shared<MappingElementFactory>(
            MakeDrawerFactory(), DisplayRulesetFactoryFactory().Make(renderOptions));
        auto elementManager = MakeMappingElementManager(*elementFactory, *container.dependencyLoader);

        // ASR loader
        asrHandlers.RegisterHandler(
            std::make_shared<MappingRenderOptionsAsrLoader>(*elementManager, renderOptions, *container.airfields));

        // Renders the mapping elements
        radarRenderables.RegisterRenderer(
            radarRenderables.ReserveRendererIdentifier(),
            std::make_shared<MappingRenderer>(elementManager),
            RadarScreen::RadarRenderableCollection::beforeTags);

        // Renders the options
        std::shared_ptr<Components::Checkbox> vrpCheckbox = Components::Checkbox::Create(
            std::make_shared<VisualReferencePointCheckboxProvider>(renderOptions),
            radarRenderables.ReserveScreenObjectIdentifier());
        radarRenderables.RegisterScreenObject(vrpCheckbox);

        auto optionsRendererId = radarRenderables.ReserveRendererIdentifier();
        radarRenderables.RegisterRenderer(
            optionsRendererId,
            std::make_shared<MappingOptionsRenderer>(
                renderOptions, vrpCheckbox, Components::ScrollbarFactory(radarRenderables)),
            RadarScreen::RadarRenderableCollection::afterLists);

        // Toggles the options
        auto toggleOptionsRendererId = radarRenderables.ReserveRendererIdentifier();
        radarRenderables.RegisterRenderer(
            toggleOptionsRendererId,
            std::make_shared<ToggleMappingOptionsRender>(
                renderOptions, radarRenderables.ReserveScreenObjectIdentifier(toggleOptionsRendererId)),
            RadarScreen::RadarRenderableCollection::afterLists);
    }
} // namespace UKControllerPlugin::Mapping
