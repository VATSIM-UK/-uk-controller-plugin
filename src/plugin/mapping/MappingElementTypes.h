#pragma once

namespace UKControllerPlugin::Mapping {

    class MappingElementTypes
    {
        public:
        [[nodiscard]] static auto TypeKnown(const std::string& type) -> bool;
        [[nodiscard]] static auto VisualReferencePoint() -> std::string;

        private:
        MappingElementTypes() = default;
    };
} // namespace UKControllerPlugin::Mapping
