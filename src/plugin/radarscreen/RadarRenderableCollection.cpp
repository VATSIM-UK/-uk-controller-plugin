#include "pch/pch.h"
#include "radarscreen/RadarRenderableCollection.h"
#include "radarscreen/RadarRenderableInterface.h"
#include "radarscreen/ScreenObjectInterface.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"

using UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface;
using UKControllerPlugin::RadarScreen::RadarRenderableInterface;
namespace UKControllerPlugin {
    namespace RadarScreen {

        /*
            Constructor, sets the default values.
        */
        RadarRenderableCollection::RadarRenderableCollection(void)
        {
            this->nextRendererId = 1;
            this->nextScreenObjectId = 1;
        }

        /*
            Returns the total number of renderers.
        */
        size_t RadarRenderableCollection::CountRenderers(void) const
        {
            return this->allRenderers.size();
        }

        /*
            Returns the total number of renderers for a given rendering phase.
        */
        size_t RadarRenderableCollection::CountRenderersInPhase(int phase) const
        {
            if (phase == this->initialPhase) {
                return this->initialPhaseRenders.size();
            } else if (phase == this->beforeTags) {
                return this->beforeTagRenders.size();
            } else if (phase == this->afterTags) {
                return this->afterTagRenders.size();
            } else if (phase == this->afterLists) {
                return this->afterListRenders.size();
            }

            throw std::invalid_argument("Invalid rendering phase");
        }

        /*
            Returns the total number of screen objects registered.
        */
        size_t RadarRenderableCollection::CountScreenObjects(void) const
        {
            return this->screenObjectMap.size() + this->screenObjects.size();
        }

        /*
            Returns the renderer ID for which a particular screen object ID is reserved.
        */
        int RadarRenderableCollection::GetRendererIdForScreenObject(int objectId) const
        {
            if (this->screenObjectMap.count(objectId) == 0) {
                throw std::invalid_argument("Invalid object id");
            }

            return this->screenObjectMap.at(objectId);
        }

        /*
            Tell the renderer that a screen object has been left clicked.
        */
        void RadarRenderableCollection::LeftClickScreenObject(
            EuroscopeRadarLoopbackInterface& radarScreen,
            int objectId,
            std::string objectDescription,
            POINT mousePos,
            RECT itemArea) const
        {
            if (this->screenObjectMap.contains(objectId)) {
                this->allRenderers.at(this->screenObjectMap.at(objectId))
                    ->LeftClick(radarScreen, objectId, objectDescription, mousePos, itemArea);
            } else if (this->screenObjects.contains(objectId)) {
                this->screenObjects.at(objectId)->LeftClick(radarScreen, objectDescription, mousePos);
            }
        }

        /*
            Moves the given screen object.
        */
        void RadarRenderableCollection::MoveScreenObject(int objectId, std::string objectDes, RECT position) const
        {
            if (this->screenObjectMap.contains(objectId)) {
                this->allRenderers.at(this->screenObjectMap.at(objectId))->Move(position, objectDes);
            } else if (this->screenObjects.contains(objectId)) {
                this->screenObjects.at(objectId)->Drag(objectDes, position);
            }
        }

        /*
            Registers a renderer for a specific phase. Returns the renderer ID.
        */
        void RadarRenderableCollection::RegisterRenderer(
            int rendererId, std::shared_ptr<RadarRenderableInterface> renderer, int renderPhase)
        {
            // Don't allow duplicate renderers
            if (this->allRenderers.count(rendererId) != 0) {
                throw std::invalid_argument("Renderer already exists!");
            }

            // Only accept renderers in a given phase.
            if (renderPhase == this->initialPhase) {
                this->initialPhaseRenders.push_back(rendererId);
            } else if (renderPhase == this->beforeTags) {
                this->beforeTagRenders.push_back(rendererId);
            } else if (renderPhase == this->afterTags) {
                this->afterTagRenders.push_back(rendererId);
            } else if (renderPhase == this->afterLists) {
                this->afterListRenders.push_back(rendererId);
            } else {
                throw std::invalid_argument("Invalid rendering phase");
            }

            this->allRenderers[rendererId] = renderer;
        }

        /*
            "Reserves" a renderer id. Doesn't stop anyone else from using it, but
            means that future calls asking for the next id won't get it.
        */
        int RadarRenderableCollection::ReserveRendererIdentifier(void)
        {
            if (this->allRenderers.count(this->nextRendererId) != 0) {
                this->nextRendererId++;
                return this->ReserveRendererIdentifier();
            }

            return this->nextRendererId++;
        }

        /*
            Reserves a specific screen object ID for a particular renderer. Returns the ID
            so that the renderer can assign it to whichever object it pleases.
        */
        int RadarRenderableCollection::ReserveScreenObjectIdentifier(int rendererId)
        {
            if (this->nextRendererId <= rendererId) {
                throw std::invalid_argument("Invalid renderer");
            }

            this->screenObjectMap[nextScreenObjectId] = rendererId;
            return this->nextScreenObjectId++;
        }

        /*
            Selects the correct phase to render and renders it.
        */
        void RadarRenderableCollection::Render(
            int phase,
            UKControllerPlugin::Windows::GdiGraphicsInterface& graphics,
            UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const
        {
            if (phase == this->initialPhase) {
                this->RenderGroup(this->initialPhaseRenders, graphics, radarScreen);
            } else if (phase == this->beforeTags) {
                this->RenderGroup(this->beforeTagRenders, graphics, radarScreen);
            } else if (phase == this->afterTags) {
                this->RenderGroup(this->afterTagRenders, graphics, radarScreen);
            } else if (phase == this->afterLists) {
                this->RenderGroup(this->afterListRenders, graphics, radarScreen);
            } else {
                LogError("Invalid rendering phase " + std::to_string(phase));
            }
        }

        /*
            Tell the renderer that a screen object has been right clicked.
        */
        void RadarRenderableCollection::RightClickScreenObject(
            int objectId,
            std::string objectDescription,
            UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const
        {
            if (this->screenObjectMap.contains(objectId)) {
                this->allRenderers.at(this->screenObjectMap.at(objectId))
                    ->RightClick(objectId, objectDescription, radarScreen);
            } else if (this->screenObjects.contains(objectId)) {
                this->screenObjects.at(objectId)->RightClick(radarScreen, objectDescription);
            }
        }

        /*
            Renders a given group of renderers.
        */
        void RadarRenderableCollection::RenderGroup(
            const std::vector<int>& group,
            UKControllerPlugin::Windows::GdiGraphicsInterface& graphics,
            UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const
        {
            for (std::vector<int>::const_iterator it = group.cbegin(); it != group.cend(); ++it) {
                if (this->allRenderers.at(*it)->IsVisible()) {
                    this->allRenderers.at(*it)->Render(graphics, radarScreen);
                }
            }
        }

        /*
            Process the command and see if its the reset visuals command.
        */
        void RadarRenderableCollection::ResetPosition(void) const
        {
            for (std::map<int, std::shared_ptr<RadarRenderableInterface>>::const_iterator it =
                     this->allRenderers.cbegin();
                 it != this->allRenderers.cend();
                 ++it) {
                it->second->ResetPosition();
            }
        }
        void RadarRenderableCollection::RegisterScreenObject(std::shared_ptr<ScreenObjectInterface> screenObject)
        {
            screenObjects[screenObject->ScreenObjectId()] = screenObject;
        }

        auto RadarRenderableCollection::ReserveScreenObjectIdentifier() -> int
        {
            return nextScreenObjectId++;
        }
    } // namespace RadarScreen
} // namespace UKControllerPlugin
