#include "MappingElementDrawerFactoryDelegator.h"
#include "MappingElementDrawerFactoryFactory.h"
#include "MappingElementTypes.h"
#include "VisualReferencePointDrawerFactory.h"

namespace UKControllerPlugin::Mapping {
    auto MakeDrawerFactory() -> std::shared_ptr<MappingElementDrawerFactory>
    {
        return std::make_shared<MappingElementDrawerFactoryDelegator>(
            std::map<std::string, std::shared_ptr<MappingElementDrawerFactory>>{
                {MappingElementTypes::VisualReferencePoint(), std::make_shared<VisualReferencePointDrawerFactory>()}});
    }
} // namespace UKControllerPlugin::Mapping
