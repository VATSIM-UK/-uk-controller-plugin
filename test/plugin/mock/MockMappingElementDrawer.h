#pragma once
#include "mapping/MappingElementDrawer.h"

using UKControllerPlugin::Euroscope::EuroscopeRadarLoopbackInterface;
using UKControllerPlugin::Mapping::MappingElementDrawer;
using UKControllerPlugin::Windows::GdiGraphicsInterface;

namespace UKControllerPluginTest::Mapping {
    class MockMappingElementDrawer : public MappingElementDrawer
    {
        public:
        MOCK_METHOD(void, Draw, (GdiGraphicsInterface&, EuroscopeRadarLoopbackInterface&), (override));
    };
} // namespace UKControllerPluginTest::Mapping
