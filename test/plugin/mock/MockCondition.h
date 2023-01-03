#pragma once
#include "intention/Condition.h"

namespace UKControllerPluginTest::IntentionCode {
    class MockCondition : public UKControllerPlugin::IntentionCode::Condition
    {
        public:
        MOCK_METHOD(
            bool,
            Passes,
            (const UKControllerPlugin::Euroscope::EuroScopeCFlightPlanInterface&,
             const UKControllerPlugin::Euroscope::EuroScopeCRadarTargetInterface&),
            (override));
    };
} // namespace UKControllerPluginTest::IntentionCode
