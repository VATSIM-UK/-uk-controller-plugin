#pragma once

namespace UKControllerPlugin::Mapping {
    /**
     * Has all the options for rendering mapping elements.
     */
    class MappingRenderOptions
    {
        public:
        void ShowOptions(bool show);
        [[nodiscard]] auto ShowOptions() const -> bool;
        void ShowVisualReferencePoints(bool show);
        [[nodiscard]] auto ShowVisualReferencePoints() const -> bool;
        void VisualReferencePointAirfields(const std::set<int> airfields);
        [[nodiscard]] auto VisualReferencePointAirfields() const -> const std::set<int>&;

        private:
        // Do we display the options
        bool showOptions = false;

        // Do we display VRPs
        bool showVisualReferencePoints = false;

        // The airfields to render
        std::set<int> visualReferencePointAirfields;
    };
} // namespace UKControllerPlugin::Mapping
