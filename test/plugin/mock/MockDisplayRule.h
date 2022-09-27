#pragma once
#include "mapping/DisplayRule.h"

namespace UKControllerPluginTest::Mapping {
    class MockDisplayRule : public UKControllerPlugin::Mapping::DisplayRule
    {
        public:
        MOCK_METHOD(bool, Passes, (), (override));
    };
} // namespace UKControllerPluginTest::Mapping
