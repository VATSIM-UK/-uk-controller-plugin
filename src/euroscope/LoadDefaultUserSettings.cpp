#include "pch/stdafx.h"
#include "euroscope/LoadDefaultUserSettings.h"
#include "euroscope/UserSetting.h"
#include "euroscope/GeneralSettingsEntries.h"

using UKControllerPlugin::Euroscope::UserSetting;
using UKControllerPlugin::Euroscope::GeneralSettingsEntries;

namespace UKControllerPlugin {
    namespace Euroscope {
        void LoadDefaultUserSettings(UserSetting & userSetting)
        {
            // Prenotes
            if (!userSetting.HasEntry(GeneralSettingsEntries::usePrenoteSettingsKey)) {
                LogInfo("Loading default value for setting " + GeneralSettingsEntries::usePrenoteSettingsKey);
                userSetting.Save(
                    GeneralSettingsEntries::usePrenoteSettingsKey,
                    GeneralSettingsEntries::usePrenoteSettingsDescription,
                    false
                );
            }

            // Automatic squawk assignment
            if (!userSetting.HasEntry(GeneralSettingsEntries::squawkToggleSettingsKey)) {
                LogInfo("Loading default value for setting " + GeneralSettingsEntries::squawkToggleSettingsKey);
                userSetting.Save(
                    GeneralSettingsEntries::squawkToggleSettingsKey,
                    GeneralSettingsEntries::squawkToggleSettingsDescription,
                    true
                );
            }

            // Automatic initial altitude assignment
            if (!userSetting.HasEntry(GeneralSettingsEntries::initialAltitudeToggleSettingsKey)) {
                LogInfo(
                    "Loading default value for setting " + GeneralSettingsEntries::initialAltitudeToggleSettingsKey
                );
                userSetting.Save(
                    GeneralSettingsEntries::initialAltitudeToggleSettingsKey,
                    GeneralSettingsEntries::initialAltitudeToggleSettingsDescription,
                    true
                );
            }
        }
    }  // namespace Euroscope
}  // namespace UKControllerPlugin
