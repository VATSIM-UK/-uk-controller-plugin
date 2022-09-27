#pragma once

namespace UKControllerPlugin {
    namespace Windows {
        class GdiGraphicsInterface;
    } // namespace Windows
    namespace Euroscope {
        class EuroscopeRadarLoopbackInterface;
    } // namespace Euroscope
    namespace RadarScreen {
        class RadarRenderableInterface;
        class ScreenObjectInterface;
    } // namespace RadarScreen
} // namespace UKControllerPlugin

namespace UKControllerPlugin::RadarScreen {

    /*
        A collection of objects that render things to the screen.
    */
    class RadarRenderableCollection
    {
        public:
        RadarRenderableCollection();
        [[nodiscard]] auto CountRenderers() const -> size_t;
        [[nodiscard]] auto CountRenderersInPhase(int phase) const -> size_t;
        [[nodiscard]] auto CountScreenObjects() const -> size_t;
        [[nodiscard]] auto GetRendererIdForScreenObject(int objectId) const -> int;
        void LeftClickScreenObject(
            UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
            int objectId,
            std::string objectDescription,
            POINT mousePos,
            RECT itemArea) const;
        void MoveScreenObject(int objectId, std::string objectDescription, RECT position) const;
        void RegisterRenderer(
            int rendererId,
            std::shared_ptr<UKControllerPlugin::RadarScreen::RadarRenderableInterface> renderer,
            int renderPhase);
        auto ReserveRendererIdentifier() -> int;
        auto ReserveScreenObjectIdentifier(int rendererId) -> int;
        auto ReserveScreenObjectIdentifier() -> int;
        void RegisterScreenObject(std::shared_ptr<ScreenObjectInterface> screenObject);
        void Render(
            int phase,
            UKControllerPlugin::Windows::GdiGraphicsInterface& graphics,
            UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const;
        void RightClickScreenObject(
            int objectId,
            std::string objectDescription,
            UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const;
        void ResetPosition() const;

        // Constant dictating that rendering should take place in the initial bitmap
        inline static const int initialPhase = 0;

        // Constant dictating that rendering should take place before tags
        inline static const int beforeTags = 1;

        // Constant to dictate that rendering should take place after tags
        inline static const int afterTags = 2;

        // Constant to dicatate that rendering should take place after lists.
        inline static const int afterLists = 3;

        private:
        void RenderGroup(
            const std::vector<int>& group,
            UKControllerPlugin::Windows::GdiGraphicsInterface& graphics,
            UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface& radarScreen) const;

        // All the renderers to render during the initial phase
        std::vector<int> initialPhaseRenders;

        // All the renderers to render before tags
        std::vector<int> beforeTagRenders;

        // All the renderers to render after tags
        std::vector<int> afterTagRenders;

        // All the renderers to render after lists
        std::vector<int> afterListRenders;

        // Map of all the renderers
        std::map<int, std::shared_ptr<RadarRenderableInterface>> allRenderers;

        // Maps a given screen object ID to a given renderer.
        std::map<int, int> screenObjectMap;
        std::map<int, std::shared_ptr<ScreenObjectInterface>> screenObjects;

        // The next renderer ID available for use - used to link screen objects to classes
        int nextRendererId;

        // The next available screen object ID
        int nextScreenObjectId;
    };
} // namespace UKControllerPlugin::RadarScreen
