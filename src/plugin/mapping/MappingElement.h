#pragma once
#include "MappingElementInterface.h"

namespace UKControllerPlugin::Mapping {
    class DisplayRule;
    class MappingElementDrawer;

    /**
     * Represents something that can be drawn onto the map.
     */
    class MappingElement : public MappingElementInterface
    {
        public:
        MappingElement(
            int id,
            std::string type,
            std::string label,
            std::set<std::shared_ptr<DisplayRule>> displayRules,
            std::shared_ptr<MappingElementDrawer> drawer);
        [[nodiscard]] auto Id() const -> int override;
        [[nodiscard]] auto Type() const -> const std::string& override;
        [[nodiscard]] auto Label() const -> const std::string& override;
        [[nodiscard]] auto ShouldDisplay() const -> bool override;
        [[nodiscard]] auto Drawer() const -> std::shared_ptr<MappingElementDrawer>;
        void Draw(Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
            override;

        private:
        // The id of the element, is only unique within a type
        int id;

        // The type of the element, e.g. visual_reference_point
        std::string type;

        // The label that accompanies the element.
        std::string label;

        // Display rules
        std::set<std::shared_ptr<DisplayRule>> displayRules;

        // Draws the element
        std::shared_ptr<MappingElementDrawer> drawer;
    };
} // namespace UKControllerPlugin::Mapping
