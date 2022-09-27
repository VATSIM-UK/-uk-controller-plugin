#include "DisplayRule.h"
#include "MappingElement.h"
#include "MappingElementDrawer.h"

namespace UKControllerPlugin::Mapping {

    MappingElement::MappingElement(
        int id,
        std::string type,
        std::string label,
        std::set<std::shared_ptr<DisplayRule>> displayRules,
        std::shared_ptr<MappingElementDrawer> drawer)
        : id(id), type(std::move(type)), label(std::move(label)), displayRules(std::move(displayRules)),
          drawer(std::move(drawer))
    {
    }

    auto MappingElement::Id() const -> int
    {
        return id;
    }

    auto MappingElement::Type() const -> const std::string&
    {
        return type;
    }

    auto MappingElement::Label() const -> const std::string&
    {
        return label;
    }

    auto MappingElement::ShouldDisplay() const -> bool
    {
        for (const auto& rule : displayRules) {
            if (!rule->Passes()) {
                return false;
            }
        }

        return true;
    }

    void MappingElement::Draw(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        this->drawer->Draw(graphics, radarScreen);
    }

    auto MappingElement::Drawer() const -> std::shared_ptr<MappingElementDrawer>
    {
        return drawer;
    }
} // namespace UKControllerPlugin::Mapping
