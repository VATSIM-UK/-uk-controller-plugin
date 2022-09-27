#pragma once
#include "components/CheckboxProviderInterface.h"

namespace UKControllerPlugin::Mapping {
    class MappingRenderOptions;

    /**
     * Provides the visual reference point checkbox
     */
    class VisualReferencePointCheckboxProvider : public Components::CheckboxProviderInterface
    {
        public:
        VisualReferencePointCheckboxProvider(std::shared_ptr<MappingRenderOptions> renderOptions);
        auto Label() -> std::string override;
        void StateChanged(bool checked) override;

        private:
        // The render options
        std::shared_ptr<MappingRenderOptions> renderOptions;
    };
} // namespace UKControllerPlugin::Mapping
