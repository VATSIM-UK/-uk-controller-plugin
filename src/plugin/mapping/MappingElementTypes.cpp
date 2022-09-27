#include "MappingElementTypes.h"

namespace UKControllerPlugin::Mapping {

    auto MappingElementTypes::VisualReferencePoint() -> std::string
    {
        return "visual_reference_point";
    }

    auto MappingElementTypes::TypeKnown(const std::string& type) -> bool
    {
        return type == VisualReferencePoint();
    }
} // namespace UKControllerPlugin::Mapping
